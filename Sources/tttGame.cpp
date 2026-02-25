#include <QVBoxLayout>
#include <QGridLayout>
#include <QMessageBox>

#include "tttGeneral.h"
#include "tttGameMenu.h"

#include "tttGame.h"

using namespace UI;

TTTGame::TTTGame(QWidget *parent): super(parent),
fieldButtonsLayout(nullptr),
mainLayout(nullptr),
matchResult(),
fieldButtons()
{
	mainLayout = new QVBoxLayout(this);
	constexpr QSize windowSize(1000, 800);
	setFixedSize(windowSize);

	const std::shared_ptr<Logic::GameState>& gameState = matchResult.currentGameState;

	// Initialize game buttons
	{
		fieldButtonsLayout = new QGridLayout;

		for (int index = 0; index < (int)fieldButtons.size(); index++)
		{
			QPushButton* const gameButton = new QPushButton(this);
			gameButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
			connect(gameButton, &QPushButton::clicked, this, &TTTGame::OnFieldButtonPressed);

			fieldButtons[index] = gameButton;
			fieldButtonsLayout->addWidget(gameButton, index / General::gEdgeSize, index % General::gEdgeSize);
		}

		mainLayout->addLayout(fieldButtonsLayout, 2);
	}

	// Initialize Game menu.
	{
		gameMenu = new TTTGameMenu(gameState, this);
		connect(gameMenu, &TTTGameMenu::InitializeRound, this, &TTTGame::InitializeGameRound);
		connect(this, &TTTGame::ResetGameMenuLabels, gameMenu, &TTTGameMenu::ResetLabels);
		mainLayout->addWidget(gameMenu, 1);
	}
}

TTTGame::~TTTGame()
{

}

void TTTGame::OnFieldButtonPressed()
{
	std::shared_ptr<Logic::GameState>& gameState = matchResult.currentGameState;
	if (!gameState->IsGameInProgress)
		return;

	QPushButton* const fieldButton = qobject_cast<QPushButton*>(sender());
	if (fieldButton == nullptr || fieldButton->text() != General::gEmptyString)
		return;

	const bool isXTurn = gameState->IsXTurn;
	gameState->Turns++;

	// Marking field button with active player's string and checking if player has won.
	const QString fieldButtonString = isXTurn ? General::gXPlayerString : General::gOPlayerString;
	fieldButton->setText(fieldButtonString);
	UpdateResultForPressedButton(*fieldButton);
	static constexpr int kMinimumRoundsPlayed = 5;
	const bool didWin = gameState->Turns < kMinimumRoundsPlayed ? false : matchResult.DidPlayerWinner(isXTurn ? General::gXPlayerWinSum : General::gOPlayerWinSum);

	QMessageBox winMessage(this);
	winMessage.setIcon(QMessageBox::Information);

	if (didWin)
	{
		if (isXTurn)
		{
			gameState->XWins++;
		}
		else
		{
			gameState->OWins++;
		}

		winMessage.setText(QString("Player \"%1\" has won the current round.").arg(fieldButtonString));
		winMessage.exec();

		// When a player won then the losing player should start in the next round.
		gameState->IsXTurn = !isXTurn;
		InitializeGameRound();
		return;
	}

	if (gameState->Turns == 9)
	{
		winMessage.setText("No Player has won the current round. It's a draw.");
		winMessage.exec();

		gameState->IsXTurn = true;
		InitializeGameRound();
		return;
	}

	// Updating for next turn if there is no winner and more turns left.
	const QString nextPlayerTurnString = isXTurn ? General::gOPlayerTurnString : General::gXPlayerTurnString;
	gameMenu->SetNextPlayerString(nextPlayerTurnString);
	gameState->IsXTurn = !isXTurn;
}

void TTTGame::InitializeGameRound()
{
	// Clear field and initialize game state.
	for (QPushButton* const gameButton : fieldButtons)
	{
		if (gameButton == nullptr)
			continue;

		gameButton->setText(General::gEmptyString);
	}
	std::shared_ptr<Logic::GameState>& gameState = matchResult.currentGameState;
	gameState->Turns = 0;
	gameState->IsGameInProgress = false;
	matchResult.InitializeResultMatrix();

	// Update game labels
	emit ResetGameMenuLabels();
}

void TTTGame::UpdateResultForPressedButton(const QPushButton& pressedPushButton)
{
	if (pressedPushButton.text().isEmpty())
		return;

	// Update the result matrix with the new marked button.
	for (int columnIndex = 0; columnIndex < (int)fieldButtonsLayout->columnCount(); columnIndex++)
	{
		for (int rowIndex = 0; rowIndex < (int)fieldButtonsLayout->rowCount(); rowIndex++)
		{
			QLayoutItem* const fieldButtonItem = fieldButtonsLayout->itemAtPosition(rowIndex, columnIndex);
			if (fieldButtonItem == nullptr)
				continue;

			QPushButton* const pushButton = qobject_cast<QPushButton*>(fieldButtonItem->widget());
			if (pushButton != &pressedPushButton)
				continue;

			const int matrixEntry = matchResult.currentGameState->IsXTurn ? General::gXPlayerWinSum / General::gEdgeSize : General::gOPlayerWinSum / General::gEdgeSize;
			matchResult.UpdateResultMatrix(columnIndex, rowIndex, matrixEntry);
			break;
		}
	}
}

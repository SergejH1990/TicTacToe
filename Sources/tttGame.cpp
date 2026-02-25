#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMessageBox>

#include "tttGeneral.h"

#include "tttGame.h"

using namespace UI;

TTTGame::TTTGame(QWidget *parent): super(parent),
gameStateLabel(nullptr),
playerTurnLabel(nullptr),
scoreLabel(nullptr),
startButton(nullptr),
resetButton(nullptr),
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
		QVBoxLayout* const menuLayout = new QVBoxLayout;

		scoreLabel = new QLabel;
		scoreLabel->setText(General::gFormatScoreString.arg(gameState->XWins).arg(gameState->OWins));
		scoreLabel->setAlignment(Qt::AlignCenter);
		menuLayout->addWidget(scoreLabel);

		playerTurnLabel = new QLabel;
		playerTurnLabel->setText(General::gNoPlayersTurnString);
		playerTurnLabel->setAlignment(Qt::AlignCenter);
		menuLayout->addWidget(playerTurnLabel);

		gameStateLabel = new QLabel;
		gameStateLabel->setText(General::gGameIdleString);
		gameStateLabel->setAlignment(Qt::AlignCenter);
		menuLayout->addWidget(gameStateLabel);

		QHBoxLayout* const gameMenuLayout = new QHBoxLayout;
		menuLayout->addLayout(gameMenuLayout);

		startButton = new QPushButton(this);
		startButton->setText("Start");
		connect(startButton, &QPushButton::clicked, this, &TTTGame::OnStartGamePressed);

		resetButton = new QPushButton(this);
		resetButton->setText("Reset");
		connect(resetButton, &QPushButton::clicked, this, &TTTGame::OnResetButtonPressed);

		gameMenuLayout->addWidget(startButton);
		gameMenuLayout->addWidget(resetButton);
		mainLayout->addLayout(menuLayout, 1);
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
	playerTurnLabel->setText(nextPlayerTurnString);
	gameState->IsXTurn = !isXTurn;
}

void TTTGame::OnStartGamePressed()
{
	std::shared_ptr<Logic::GameState>& gameState = matchResult.currentGameState;
	if (gameState->IsGameInProgress)
		return;

	gameState->IsGameInProgress = true;
	const QString nextPlayerTurnString = gameState->IsXTurn ? General::gXPlayerTurnString : General::gOPlayerTurnString;

	playerTurnLabel->setText(nextPlayerTurnString);
	gameStateLabel->setText(General::gGameProgressString);
}

void TTTGame::OnResetButtonPressed()
{
	std::shared_ptr<Logic::GameState>& gameState = matchResult.currentGameState;
	gameState->XWins = 0;
	gameState->OWins = 0;

	gameState->IsXTurn = true;
	InitializeGameRound();
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
	scoreLabel->setText(General::gFormatScoreString.arg(gameState->XWins).arg(gameState->OWins));
	playerTurnLabel->setText(General::gNoPlayersTurnString);
	gameStateLabel->setText(General::gGameIdleString);
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

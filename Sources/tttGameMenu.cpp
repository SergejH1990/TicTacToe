
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

#include "tttGeneral.h"

#include "tttGameMenu.h"

using namespace UI;

TTTGameMenu::TTTGameMenu(std::shared_ptr<Logic::TTTGameState>& gameState, QWidget *parent) :
super(parent),
gameStateLabel(nullptr),
playerTurnLabel(nullptr),
scoreLabel(nullptr),
startButton(nullptr),
resetButton(nullptr),
currentGameState(gameState)
{
	QVBoxLayout* const menuLayout = new QVBoxLayout(this);

	scoreLabel = new QLabel;
	scoreLabel->setText(General::gFormatScoreString.arg(currentGameState->XWins).arg(currentGameState->OWins));
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
	connect(startButton, &QPushButton::clicked, this, &TTTGameMenu::OnStartGamePressed);

	resetButton = new QPushButton(this);
	resetButton->setText("Reset");
	connect(resetButton, &QPushButton::clicked, this, &TTTGameMenu::OnResetButtonPressed);

	gameMenuLayout->addWidget(startButton);
	gameMenuLayout->addWidget(resetButton);
}

TTTGameMenu::~TTTGameMenu()
{

}

void TTTGameMenu::ResetLabels()
{
	scoreLabel->setText(General::gFormatScoreString.arg(currentGameState->XWins).arg(currentGameState->OWins));
	playerTurnLabel->setText(General::gNoPlayersTurnString);
	gameStateLabel->setText(General::gGameIdleString);
}

void TTTGameMenu::SetNextPlayerString(const QString& nextPlayerString)
{
	playerTurnLabel->setText(nextPlayerString);
}

void TTTGameMenu::OnStartGamePressed()
{
	if (currentGameState->IsGameInProgress)
		return;

	currentGameState->IsGameInProgress = true;
	const QString nextPlayerTurnString = currentGameState->IsXTurn ? General::gXPlayerTurnString : General::gOPlayerTurnString;

	playerTurnLabel->setText(nextPlayerTurnString);
	gameStateLabel->setText(General::gGameProgressString);
}

void TTTGameMenu::OnResetButtonPressed()
{
	currentGameState->XWins = 0;
	currentGameState->OWins = 0;

	currentGameState->IsXTurn = true;
	emit InitializeRound();
}


#include <QSize>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QLabel>
#include <QHBoxLayout>
#include <QGridLayout>

#include "TicTacToeGeneral.h"

#include "tttgame.h"

constexpr QSize kTTTGameWindowSize(1000, 800);
static const QString kTTTGameStartTurnString("Game did not start yet");
static const QString kTTTGameXPlayerTurnString("It's X Turn");
static const QString kTTTGameOPlayerTurnString("It's O Turn");
static QString TTTGameFormatScoreString("X  %1 : %2  O");

TTTGame::TTTGame(QWidget *parent): super(parent),
playerTurnLabel(nullptr),
scoreLabel(nullptr),
startButton(nullptr),
resetButton(nullptr),
gameLayout(nullptr),
mainLayout(nullptr),
gameButtons(),
xWins(0),
oWins(0),
isGameInProgress(false),
isXTurn(false)
{
	mainLayout = new QVBoxLayout(this);
	setFixedSize(kTTTGameWindowSize);

	// Initialize game buttons
	{
		gameLayout = new QGridLayout;

		for (int index = 0; index < (int)gameButtons.size(); index++)
		{
			QPushButton* const gameButton = new QPushButton(this);
			gameButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
			connect(gameButton, &QPushButton::clicked, this, &TTTGame::OnGameButtonPressed);

			gameButtons[index] = gameButton;
			gameLayout->addWidget(gameButton, index / 3, index % 3);
		}

		mainLayout->addLayout(gameLayout, 2);
	}

	// Initialize Game menu.
	{
		QVBoxLayout* const menuLayout = new QVBoxLayout;

		scoreLabel = new QLabel(this);
		scoreLabel->setText(TTTGameFormatScoreString.arg(xWins).arg(oWins));
		scoreLabel->setAlignment(Qt::AlignCenter);
		menuLayout->addWidget(scoreLabel);

		playerTurnLabel = new QLabel(this);
		playerTurnLabel->setText(kTTTGameStartTurnString);
		playerTurnLabel->setAlignment(Qt::AlignCenter);
		menuLayout->addWidget(playerTurnLabel);

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

void TTTGame::OnGameButtonPressed()
{
	if (!isGameInProgress)
		return;

	QPushButton* const gameButton = qobject_cast<QPushButton*>(sender());
	if (gameButton == nullptr || gameButton->text() != General::gEmptyString)
		return;

	if (isXTurn)
	{
		gameButton->setText("X");
		isXTurn = !isXTurn;
		playerTurnLabel->setText(kTTTGameOPlayerTurnString);
		return;
	}

	gameButton->setText("O");
	isXTurn = !isXTurn;
	playerTurnLabel->setText(kTTTGameXPlayerTurnString);
}

void TTTGame::OnStartGamePressed()
{
	if (isGameInProgress)
		return;

	isGameInProgress = true;
	isXTurn = true;

	playerTurnLabel->setText(kTTTGameXPlayerTurnString);
}

void TTTGame::OnResetButtonPressed()
{
	for (QPushButton* const gameButton : gameButtons)
	{
		if (gameButton == nullptr)
			continue;

		gameButton->setText(General::gEmptyString);
	}

	isXTurn = false;
	isGameInProgress = false;
	xWins = 0;
	oWins = 0;
	scoreLabel->setText(TTTGameFormatScoreString.arg(xWins).arg(oWins));
	playerTurnLabel->setText(kTTTGameStartTurnString);
}

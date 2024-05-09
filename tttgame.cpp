
#include <QSize>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QLabel>
#include <QHBoxLayout>
#include <QGridLayout>

#include "TicTacToeGeneral.h"

#include "tttgame.h"

static const QSize kTTTGameWindowSize(1000, 800);

TTTGame::TTTGame(QWidget *parent): super(parent),
winnerLabel(nullptr),
playerTurnLabel(nullptr),
scoreLabel(nullptr),
startButton(nullptr),
resetButton(nullptr),
gameLayout(nullptr),
mainLayout(nullptr),
gameButtons(),
isXTurn(false)
{
	mainLayout = new QVBoxLayout(this);
	setFixedSize(kTTTGameWindowSize);

	// Initialize game buttons
	{
		gameLayout = new QGridLayout;

		for (int index = 0; index < (int)gameButtons.size(); index++)
		{
			QPushButton* gameButton = gameButtons[index];
			gameButton = new QPushButton(this);
			gameButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
			connect(gameButton, &QPushButton::clicked, this, &TTTGame::placeSymbolOnButton);

			gameLayout->addWidget(gameButton, index / 3, index % 3);
		}

		mainLayout->addLayout(gameLayout, 2);
	}

	// Initialize Game menu.
	{
		QVBoxLayout* const menuLayout = new QVBoxLayout;

		scoreLabel = new QLabel(this);
		scoreLabel->setText("0 : 0");
		scoreLabel->setAlignment(Qt::AlignCenter);
		menuLayout->addWidget(scoreLabel);

		winnerLabel = new QLabel(this);
		winnerLabel->setText("No Winner");
		winnerLabel->setAlignment(Qt::AlignCenter);
		menuLayout->addWidget(winnerLabel);

		playerTurnLabel = new QLabel(this);
		playerTurnLabel->setText("Game did not start yet");
		playerTurnLabel->setAlignment(Qt::AlignCenter);
		menuLayout->addWidget(playerTurnLabel);

		QHBoxLayout* const gameMenuLayout = new QHBoxLayout;
		menuLayout->addLayout(gameMenuLayout);

		startButton = new QPushButton(this);
		startButton->setText("Start");
		connect(startButton, &QPushButton::clicked, [](){});

		resetButton = new QPushButton(this);
		resetButton->setText("Reset");
		connect(resetButton, &QPushButton::clicked, this, &TTTGame::resetFields);

		gameMenuLayout->addWidget(startButton);
		gameMenuLayout->addWidget(resetButton);
		mainLayout->addLayout(menuLayout, 1);
	}
}

TTTGame::~TTTGame()
{

}

void TTTGame::placeSymbolOnButton()
{
	QPushButton* const gameButton = qobject_cast<QPushButton*>(sender());
	if (gameButton == nullptr)
		return;

	if (isXTurn)
	{
		gameButton->setText("X");
		isXTurn = !isXTurn;
		return;
	}

	gameButton->setText("O");
	isXTurn = !isXTurn;
}

void TTTGame::resetFields()
{
}

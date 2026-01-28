
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QGridLayout>

#include "tttGeneral.h"

#include "tttGame.h"

TTTGame::TTTGame(QWidget *parent): super(parent),
playerTurnLabel(nullptr),
scoreLabel(nullptr),
startButton(nullptr),
resetButton(nullptr),
fieldButtonsLayout(nullptr),
mainLayout(nullptr),
fieldButtons(),
xWins(0),
oWins(0),
turns(0),
isGameInProgress(false),
isXTurn(false)
{
	mainLayout = new QVBoxLayout(this);
	setFixedSize(General::gWindowSize);

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
		scoreLabel->setText(General::gFormatScoreString.arg(xWins).arg(oWins));
		scoreLabel->setAlignment(Qt::AlignCenter);
		menuLayout->addWidget(scoreLabel);

        playerTurnLabel = new QLabel;
		playerTurnLabel->setText(General::gStartGameString);
		playerTurnLabel->setAlignment(Qt::AlignCenter);
		menuLayout->addWidget(playerTurnLabel);

        gameStateLabel = new QLabel;
        gameStateLabel->setText(General::gStartGameString);
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
	if (!isGameInProgress)
		return;

	QPushButton* const gameButton = qobject_cast<QPushButton*>(sender());
	if (gameButton == nullptr || gameButton->text() != General::gEmptyString)
		return;

    const QString gameButtonString = isXTurn ? General::gXPlayerString : General::gOPlayerString;
    const QString playerTurnString = isXTurn ? General::gOPlayerTurnString : General::gXPlayerTurnString;
    turns++;
    gameButton->setText(gameButtonString);
    const bool didWin = IsWinner(*gameButton);

    if (didWin)
    {
        if (isXTurn)
        {
            xWins++;
        }
        else
        {
            oWins++;
        }
        ResetGame();
    }
    else if (turns == 9)
    {
        ResetGame();
    }

    playerTurnLabel->setText(playerTurnString);
    isXTurn = !isXTurn;
}

void TTTGame::OnStartGamePressed()
{
	if (isGameInProgress)
		return;

	isGameInProgress = true;
	isXTurn = true;

	playerTurnLabel->setText(General::gXPlayerTurnString);
}

void TTTGame::OnResetButtonPressed()
{
	xWins = 0;
	oWins = 0;

    ResetGame();

	isGameInProgress = false;
	playerTurnLabel->setText(General::gStartGameString);
}

void TTTGame::ResetGame()
{
    for (QPushButton* const gameButton : fieldButtons)
	{
		if (gameButton == nullptr)
			continue;

		gameButton->setText(General::gEmptyString);
	}

	isXTurn = false;
	turns = 0;

	scoreLabel->setText(General::gFormatScoreString.arg(xWins).arg(oWins));
}

bool TTTGame::IsWinner(const QPushButton& pressedPushButton)
{
    if (pressedPushButton.text().isEmpty() || turns < General::gEdgeSize)
		return false;

    const QString pressedButtonText = pressedPushButton.text();
	std::array<std::array<int, General::gEdgeSize>, General::gEdgeSize> resultMatrix;
    for (int columnIndex = 0; columnIndex < (int)fieldButtonsLayout->columnCount(); columnIndex++)
	{
        for (int rowIndex = 0; rowIndex < (int)fieldButtonsLayout->rowCount(); rowIndex++)
		{
            QPushButton* const pushButton = qobject_cast<QPushButton*>(fieldButtonsLayout->itemAtPosition(rowIndex, columnIndex)->widget());
			if (pushButton == nullptr)
				continue;

			const QString buttonText = pushButton->text();
			if (buttonText.isEmpty() || buttonText != pressedButtonText)
			{
				resultMatrix[columnIndex][rowIndex] = 0;
			}
			else
			{
				resultMatrix[columnIndex][rowIndex] = 1;
			}
		}
	}

	int sumDiagonal1 = 0;
	int sumDiagonal2 = 0;
	int sumRow1 = 0;
	int sumRow2 = 0;
	int sumRow3 = 0;
	int sumColumn1 = 0;
	int sumColumn2 = 0;
	int sumColumn3 = 0;
	for (int index = 0; index < General::gEdgeSize; index++)
	{
		sumDiagonal1 += resultMatrix[index][index];
		sumDiagonal2 += resultMatrix[General::gEdgeSize - index - 1][index];
		sumRow1 += resultMatrix[index][0];
		sumRow2 += resultMatrix[index][1];
		sumRow3 += resultMatrix[index][2];
		sumColumn1 += resultMatrix[0][index];
		sumColumn2 += resultMatrix[1][index];
		sumColumn3 += resultMatrix[2][index];
	}

	return sumDiagonal1 == General::gEdgeSize || sumDiagonal2 == General::gEdgeSize || sumRow1 == General::gEdgeSize || sumRow2 == General::gEdgeSize ||
			sumRow3 == General::gEdgeSize || sumColumn1 == General::gEdgeSize || sumColumn2 == General::gEdgeSize || sumColumn3 == General::gEdgeSize;
}

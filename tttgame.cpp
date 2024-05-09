
#include <QPushButton>
#include <QPropertyAnimation>
#include <QLabel>
#include <QHBoxLayout>
#include <QGridLayout>

#include "TicTacToeGeneral.h"

#include "tttgame.h"

TTTGame::TTTGame(QWidget *parent): super(parent),
topLeftButton(nullptr),
topMiddleButton(nullptr),
topRightButton(nullptr),
centerLeftButton(nullptr),
centerMiddleButton(nullptr),
centerRightButton(nullptr),
bottomLeftButton(nullptr),
bottomMiddleButton(nullptr),
bottomRightBUtton(nullptr),
winnerLabel(nullptr),
playerTurnLabel(nullptr),
startButton(nullptr),
resetButton(nullptr),
gameLayout(nullptr),
mainLayout(nullptr)
{
    mainLayout = new QVBoxLayout(this);
    setFixedSize(1000, 600);

    {
        gameLayout = new QGridLayout;

        topLeftButton = new QPushButton(this);
        topLeftButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        connect(topLeftButton, &QPushButton::clicked, this, &TTTGame::animateButton);

        topMiddleButton = new QPushButton(this);
        topMiddleButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        connect(topMiddleButton, &QPushButton::clicked, this, &TTTGame::animateButton);

        topRightButton = new QPushButton(this);
        topRightButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        connect(topRightButton, &QPushButton::clicked, this, &TTTGame::animateButton);

        centerLeftButton = new QPushButton(this);
        centerLeftButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        connect(centerLeftButton, &QPushButton::clicked, this, &TTTGame::animateButton);

        centerMiddleButton = new QPushButton(this);
        centerMiddleButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        connect(centerMiddleButton, &QPushButton::clicked, this, &TTTGame::animateButton);

        centerRightButton = new QPushButton(this);
        centerRightButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        connect(centerRightButton, &QPushButton::clicked, this, &TTTGame::animateButton);

        bottomLeftButton = new QPushButton(this);
        bottomLeftButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        connect(bottomLeftButton, &QPushButton::clicked, this, &TTTGame::animateButton);

        bottomMiddleButton = new QPushButton(this);
        bottomMiddleButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        connect(bottomMiddleButton, &QPushButton::clicked, this, &TTTGame::animateButton);

        bottomRightBUtton = new QPushButton(this);
        bottomRightBUtton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        connect(bottomRightBUtton, &QPushButton::clicked, this, &TTTGame::animateButton);

        gameLayout->addWidget(topLeftButton, 0, 0);
        gameLayout->addWidget(topMiddleButton, 0, 1);
        gameLayout->addWidget(topRightButton, 0 , 2);
        gameLayout->addWidget(centerLeftButton, 1, 0);
        gameLayout->addWidget(centerMiddleButton, 1, 1);
        gameLayout->addWidget(centerRightButton, 1, 2);
        gameLayout->addWidget(bottomLeftButton, 2, 0);
        gameLayout->addWidget(bottomMiddleButton, 2, 1);
        gameLayout->addWidget(bottomRightBUtton, 2, 2);
        mainLayout->addLayout(gameLayout, 2);
    }

    {
        QVBoxLayout* const menuLayout = new QVBoxLayout;

        winnerLabel = new QLabel(this);
        winnerLabel->setText("No Winner");
        winnerLabel->setAlignment(Qt::AlignCenter);
        winnerLabel->setFont(General::gAppFont);
        menuLayout->addWidget(winnerLabel);

        playerTurnLabel = new QLabel(this);
        playerTurnLabel->setText("Turn of O");
        playerTurnLabel->setAlignment(Qt::AlignCenter);
        playerTurnLabel->setFont(General::gAppFont);
        menuLayout->addWidget(playerTurnLabel);

        QHBoxLayout* const gameMenuLayout = new QHBoxLayout;
        menuLayout->addLayout(gameMenuLayout);

        startButton = new QPushButton(this);
        startButton->setText("Start");
        startButton->setFont(General::gAppFont);
        connect(startButton, &QPushButton::clicked, [](){});

        resetButton = new QPushButton(this);
        resetButton->setText("Reset");
        resetButton->setFont(General::gAppFont);
        connect(resetButton, &QPushButton::clicked, this, &TTTGame::resetFields);

        gameMenuLayout->addWidget(startButton);
        gameMenuLayout->addWidget(resetButton);
        mainLayout->addLayout(menuLayout, 1);
    }
}

TTTGame::~TTTGame()
{

}

void TTTGame::paintField()
{
    QPushButton *button=(QPushButton*)sender();
}

void TTTGame::resetFields()
{
}

void TTTGame::animateButton()
{
    QPushButton *button = (QPushButton*)sender();
    button->raise();

    QPropertyAnimation* animation= new QPropertyAnimation(button, "geometry");
    animation->setDuration(1000);

    animation->setKeyValueAt(0, button->geometry());
    animation->setKeyValueAt(0.5, QRect(button->pos(), QSize(10, 10)));
    animation->setKeyValueAt(1, button->geometry());

    animation->start();
}

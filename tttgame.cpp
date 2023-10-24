
#include <QPushButton>
#include <QPropertyAnimation>
#include <QHBoxLayout>
#include <QGridLayout>

#include "tttgame.h"

TTTGame::TTTGame(QWidget *parent): super(parent),
topLeftButton(nullptr),
topMIddleButton(nullptr),
topRightButton(nullptr),
centerLeftButton(nullptr),
centerMiddleButton(nullptr),
centerRightButton(nullptr),
bottomLeftButton(nullptr),
bottomMiddleButton(nullptr),
bottomRightBUtton(nullptr),
startButton(nullptr),
resetButton(nullptr),
gameLayout(nullptr),
mainLayout(nullptr)
{
    mainLayout = new QHBoxLayout(this);
    setFixedSize(600, 400);

    {
        QVBoxLayout* menuLayout = new QVBoxLayout;

        startButton = new QPushButton(this);
        startButton->setText("Start");
        connect(startButton, &QPushButton::clicked, [](){});

        resetButton = new QPushButton(this);
        resetButton->setText("Reset");
        connect(resetButton, &QPushButton::clicked, this, &TTTGame::resetFields);

        menuLayout->addWidget(startButton);
        menuLayout->addWidget(resetButton);
        mainLayout->addLayout(menuLayout);
    }

    {
        gameLayout = new QGridLayout;

        topLeftButton = new QPushButton(this);
        topLeftButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        connect(topLeftButton, &QPushButton::clicked, this, &TTTGame::animateButton);

        topMIddleButton = new QPushButton(this);
        topMIddleButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        connect(topMIddleButton, &QPushButton::clicked, this, &TTTGame::animateButton);

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
        gameLayout->addWidget(topMIddleButton, 0, 1);
        gameLayout->addWidget(topRightButton, 0 , 2);
        gameLayout->addWidget(centerLeftButton, 1, 0);
        gameLayout->addWidget(centerMiddleButton, 1, 1);
        gameLayout->addWidget(centerRightButton, 1, 2);
        gameLayout->addWidget(bottomLeftButton, 2, 0);
        gameLayout->addWidget(bottomMiddleButton, 2, 1);
        gameLayout->addWidget(bottomRightBUtton, 2, 2);
        mainLayout->addLayout(gameLayout);
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

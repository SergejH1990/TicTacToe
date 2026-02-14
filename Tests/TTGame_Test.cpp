
#include "TTGame_Test.h"

TTGame_Test::TTGame_Test(QWidget *parent) : super(parent)
{
}

TTGame_Test::~TTGame_Test()
{
}

void TTGame_Test::OnFieldButtonPressed()
{
	super::OnFieldButtonPressed();
}

void TTGame_Test::OnStartGamePressed()
{
	super::OnStartGamePressed();
}

void TTGame_Test::OnResetButtonPressed()
{
	super::OnResetButtonPressed();
}

void TTGame_Test::InitializeGameRound()
{
	super::InitializeGameRound();
}

bool TTGame_Test::DidPlayerWinner(const QPushButton& pressedPushButton)
{
	return super::DidPlayerWinner(pressedPushButton);
}





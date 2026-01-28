#ifndef TTTGENERAL_H
#define TTTGENERAL_H

#include <QWidget>

// constants and strings used for the tic tac toe game screen
namespace General{
	constexpr QSize gWindowSize(1000, 800);
	constexpr int gEdgeSize = 3;
	static const QString gXPlayerString("X");
	static const QString gOPlayerString("O");
	static const QString gStartGameString("Game did not start yet");
    static const QString gGameProgressString("Game is in progress");
    static const QString gXPlayerWinString("Player X won the round");
	static const QString gXPlayerTurnString("It's X Turn");
    static const QString gOPlayerWinString("Player O won the round");
	static const QString gOPlayerTurnString("It's O Turn");
	static QString gFormatScoreString("X  %1 : %2  O");
	static const QFont gAppFont("PazoMathBlackboardBold", 20);
	static const QString gEmptyString;
}

#endif // TTTGENERAL_H

#ifndef TICTACTOEGENERAL_H
#define TICTACTOEGENERAL_H

#include <QWidget>

namespace General{
	constexpr QSize gWindowSize(1000, 800);
	constexpr int gEdgeSize = 3;
	static const QString gXPlayerString("X");
	static const QString gOPlayerString("O");
	static const QString gStartGameString("Game did not start yet");
	static const QString gXPlayerTurnString("It's X Turn");
	static const QString gOPlayerTurnString("It's O Turn");
	static QString gFormatScoreString("X  %1 : %2  O");
	static const QFont gAppFont("PazoMathBlackboardBold", 20);
	static const QString gEmptyString;
}

#endif // TICTACTOEGENERAL_H

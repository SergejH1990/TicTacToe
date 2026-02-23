#ifndef TTTGENERAL_H
#define TTTGENERAL_H

#include <QWidget>

// constants and strings used for the tic tac toe game
namespace General{

	static constexpr int gEdgeSize = 3;
	static constexpr int gXPlayerWinSum = gEdgeSize;
	static constexpr int gOPlayerWinSum = 2 * gEdgeSize;
	static const QString gXPlayerString("X");
	static const QString gOPlayerString("O");
    static const QString gGameIdleString("Game did not start yet");
    static const QString gGameProgressString("Game is in progress");
    static const QString gNoPlayersTurnString("No player is active");
	static const QString gXPlayerTurnString("It's X Turn");
	static const QString gOPlayerTurnString("It's O Turn");
	static QString gFormatScoreString("X  %1 : %2  O");
	static const QString gEmptyString;
}

#endif // TTTGENERAL_H

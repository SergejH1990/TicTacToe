#ifndef TTTMATCHRESULT_H
#define TTTMATCHRESULT_H

#include <array>

#include "tttGeneral.h"

class TTTMatchResult
{
public:
	TTTMatchResult();

	/**
	 * Initializes the result matrix components to the value of 100 so that the win sum for each player is unique.
	 */
	void InitializeResultMatrix();

	void UpdateResultMatrix(const int column, const int row, const int matrixEntry);

	/**
	 * Determines if the last set button has lead for the current player to win the game.
	 *
	 * @param playerWinSum the button that was last pressed.
	 * @return true if player is a winner false otherwise.
	 */
	bool DidPlayerWinner(const int playerWinSum);

protected:
	std::array<std::array<int, General::gEdgeSize>, General::gEdgeSize> resultMatrix; /**< Matrix which is used to track if a player has won the round. */
};

#endif // TTTMATCHRESULT_H

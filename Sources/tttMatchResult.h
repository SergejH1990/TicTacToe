#ifndef TTTMATCHRESULT_H
#define TTTMATCHRESULT_H

#include <array>
#include <memory>

#include "tttGeneral.h"

namespace Logic {

	static constexpr int gDefaultMatrixEntry = 100;

	struct GameState {
		GameState():
		XWins(0),
		OWins(0),
		Turns(0),
		IsGameInProgress(false),
		IsXTurn(true)
		{}

		int XWins; /**< Tracks the wins for Player X. */
		int OWins; /**< Tracks the wins for Player O. */
		int Turns; /**< Tracks the amount of turns played in the current round. */
		bool IsGameInProgress; /**< True if a round is being played, false if a round has finished and next one is not started yet. */
		bool IsXTurn; /**< True if it is Player X turn and false if it is Player O turn. */
	};

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

		std::shared_ptr<GameState> currentGameState;

	protected:
		std::array<std::array<int, General::gEdgeSize>, General::gEdgeSize> resultMatrix; /**< Matrix which is used to track if a player has won the round. */
	};
}

#endif // TTTMATCHRESULT_H

#ifndef TTTGAMECONTROLLER_H
#define TTTGAMECONTROLLER_H

#include <array>

#include "tttGeneral.h"
#include "tttNetworkManager.h"

namespace Logic {

	static constexpr int gDefaultMatrixEntry = 100; /**< The value given to all matrix entries that were not updated by a player yet. */

	struct TTTGameState {
		TTTGameState():
		XWins(0),
		OWins(0),
		Turns(0),
		IsGameInProgress(false),
		IsXTurn(true),
		ResultMatrix()
		{
		}

		int XWins; /**< Tracks the wins for Player X. */
		int OWins; /**< Tracks the wins for Player O. */
		int Turns; /**< Tracks the amount of turns played in the current round. */
		bool IsGameInProgress; /**< True if a round is being played, false if a round has finished and next one is not started yet. */
		bool IsXTurn; /**< True if it is Player X turn and false if it is Player O turn. */
		std::array<std::array<int, General::gEdgeSize>, General::gEdgeSize> ResultMatrix; /**< Matrix which is used to track if a player has won the round. */
	};

	class TTTGameController : public QObject
	{
		Q_OBJECT
	public:
		explicit TTTGameController(std::shared_ptr<TTTGameState>& gameState, QObject* parent = nullptr);
		virtual ~TTTGameController();

		/**
		 * Initializes the result matrix components to the value of 100 so that the win sum for each player is unique.
		 */
		void InitializeResultMatrix();

		/**
		 * Updates the result matrix at the column and row with the matrix entry value.
		 *
		 * @param column the column of the result matrix.
		 * @param row the row of the result matrix.
		 * @param matrixEntry the value the matrix will take at the column and row.
		 */
		void UpdateResultMatrix(const int column, const int row, const int matrixEntry);

		/**
		 * Determines if the last set button has lead for the current player to win the game.
		 *
		 * @param playerWinSum the button that was last pressed.
		 * @return true if player is a winner false otherwise.
		 */
		bool DidPlayerWinner(const int playerWinSum);

	protected:
		std::shared_ptr<TTTGameState> currentGameState; /**< Holds the current game state of the game. */
		Network::TTTNetworkManager* tcpNetworkManager;	/**< The network manager in charge of communication of the players when being remote. */

	private:
		using super = QObject;
	};
}

#endif // TTTGAMECONTROLLER_H

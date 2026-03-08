#ifndef TTTGAMEMENU_H
#define TTTGAMEMENU_H

#include <QWidget>

#include "tttGameController.h"

namespace UI {

	class TTTGameMenu : public QWidget
	{
		Q_OBJECT
	public:
		explicit TTTGameMenu(std::shared_ptr<Logic::TTTGameState>& gameState, QWidget *parent = nullptr);
		virtual ~TTTGameMenu();

		/**
		 * Resets the labels of the menu to the default state.
		 */
		void ResetLabels();

		/**
		 * Set the string of the player turn label to \p nextPlayerString
		 *
		 * @param nextPlayerString the string the player turn label is displaying.
		 */
		void SetNextPlayerString(const QString& nextPlayerString);

	signals:
		/**
		 * Signal used to tell the game window that the next round needs to be loaded because of a reset.
		 */
		void InitializeRound();

	protected:
		/**
		 * Processes button press of the start game button.
		 */
		void OnStartGamePressed();

		/**
		 *
		 * Processes button press of the reset game button.
		 */
		void OnResetButtonPressed();

		class QLabel* gameStateLabel; /**< The label shows in which state the game is currently. */
		class QLabel* playerTurnLabel; /**< The label displays which players turn it is currently. */
		class QLabel* scoreLabel; /**< The label displays the score between the players for the current session. */

		class QPushButton* startButton; /**< The button starts the game session. */
		class QPushButton* resetButton; /**< The button resets the game session. */

		std::shared_ptr<Logic::TTTGameState> currentGameState; /**< Holds the current game state. */

	private:
		using super = QWidget;
	};
}

#endif // TTTGAMEMENU_H

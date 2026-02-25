#ifndef TTTGAMEMENU_H
#define TTTGAMEMENU_H

#include <QWidget>

#include "tttMatchResult.h"

namespace UI {

	class TTTGameMenu : public QWidget
	{
		Q_OBJECT
	public:
		explicit TTTGameMenu(std::shared_ptr<Logic::GameState>& gameState, QWidget *parent = nullptr);
		virtual ~TTTGameMenu();

		void ResetLabels();

		void SetNextPlayerString(const QString& nextPlayerString);

	signals:
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

		std::shared_ptr<Logic::GameState> currentGameState;

	private:
		using super = QWidget;
	};
}

#endif // TTTGAMEMENU_H

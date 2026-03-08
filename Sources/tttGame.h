#ifndef TTTGAME_H
#define TTTGAME_H

#include <array>

#include <QWidget>
#include <QPushButton>

#include "tttGameController.h"

namespace UI {

	class TTTGame : public QWidget
	{
		Q_OBJECT
	public:
		explicit TTTGame(QWidget *parent = nullptr);
		virtual ~TTTGame();

	signals:
		/**
		 * Signal used to telll the game menu to reset its menu labels to the default state.
		 */
		void ResetGameMenuLabels();

	protected:
		/**
		 *  Processes button presses of the players in the game field.
		 */
		void OnFieldButtonPressed();

		/**
		 * Initialized the state of the game for the next game round after the current round is finished.
		 */
		void InitializeGameRound();

		/**
		 * Finds the pressed button on the field and updates the result matrix for it with the correct value.
		 *
		 * @param pressedPushButton the button which was pressed by the player during their turn.
		 */
		void UpdateResultForPressedButton(const QPushButton& pressedPushButton);

		class TTTGameMenu* gameMenu; /**< The instance of the menu used for the game. */

		class QGridLayout* fieldButtonsLayout; /**< Layout which contains the buttons the players are competing against each other. */
		class QVBoxLayout* mainLayout; /**< Layout which contains all widgets of the game. */

		Logic::TTTGameController* gameController; /**< The controller updates and processed the game state. */
		std::shared_ptr<Logic::TTTGameState> gameState; /**< The state the game is in during running. */

		std::array<class QPushButton*, 9> fieldButtons; /**< The buttons where the game is played. */

	private:
		using super = QWidget;
	};
}

#endif // TTTGAME_H

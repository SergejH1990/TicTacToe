#ifndef TTTGAME_H
#define TTTGAME_H

#include <array>

#include <QWidget>
#include <QPushButton>

#include "tttMatchResult.h"

namespace UI {

	class TTTGame : public QWidget
	{
		Q_OBJECT
	public:
		explicit TTTGame(QWidget *parent = nullptr);
		virtual ~TTTGame();

	signals:
		void ResetGameMenuLabels();

	protected:
		/**
		 *  Processes button presses of the players in the game field.
		 */
		void OnFieldButtonPressed();

		/**
		 * Resets the game to initial state
		 */
		void InitializeGameRound();

		void UpdateResultForPressedButton(const QPushButton& pressedPushButton);

		class TTTGameMenu* gameMenu;

		class QGridLayout* fieldButtonsLayout; /**< Layout which contains the buttons the players are competing against each other. */
		class QVBoxLayout* mainLayout; /**< Layout which contains all widgets of the game. */

		Logic::TTTMatchResult matchResult;

		std::array<class QPushButton*, 9> fieldButtons; /**< The buttons where the game is played. */

	private:
		using super = QWidget;
	};
}

#endif // TTTGAME_H

#ifndef TTTGAME_H
#define TTTGAME_H

#include <array>

#include <QWidget>

class TTTGame : public QWidget
{
	Q_OBJECT
public:
	explicit TTTGame(QWidget *parent = nullptr);
	virtual ~TTTGame();

protected:
    /**
     *  Processes button presses of the players in the game field.
     */
    void OnFieldButtonPressed();

    /**
     * Processes button press of the start game button.
     */
	void OnStartGamePressed();

    /**
     * Processes button press of the reset game button.
     */
	void OnResetButtonPressed();

    /**
     * Resets the game to initial state
     */
    void InitializeGameRound();

    /**
     * Determines if the last set button has lead for the current player to win the game.
     *
     * @param pressedPushButton the button that was last pressed.
     * @return true if player is a winner false otherwise.
     */
    bool DidPlayerWinner(const class QPushButton& pressedPushButton);

    class QLabel* gameStateLabel; /**< The label shows in which state the game is currently. */
    class QLabel* playerTurnLabel; /**< The label displays which players turn it is currently. */
    class QLabel* scoreLabel; /**< The label displays the score between the players for the current session. */

    class QPushButton* startButton; /**< The button starts the game session. */
    class QPushButton* resetButton; /**< The button resets the game session. */

    class QGridLayout* fieldButtonsLayout; /**< Layout which contains the buttons the players are competing against each other. */
    class QVBoxLayout* mainLayout; /**< Layout which contains all widgets of the game. */

    std::array<class QPushButton*, 9> fieldButtons; /**< The buttons where the game is played. */

    int xWins; /**< Tracks the wins for Player X. */
    int oWins; /**< Tracks the wins for Player O. */
    int turns; /**< Tracks the amount of turns played in the current round. */
    bool isGameInProgress; /**< True if a round is being played, false if a round has finished and next one is not started yet. */
    bool isXTurn; /**< True if it is Player X turn and false if it is Player O turn. */

private:
	using super = QWidget;
};

#endif // TTTGAME_H

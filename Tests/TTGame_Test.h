#ifndef TTGAME_TEST_H
#define TTGAME_TEST_H

#include "Sources/tttGame.h"

class TTGame_Test : public TTTGame
{
	Q_OBJECT
public:
	explicit TTGame_Test(QWidget *parent = nullptr);
	virtual ~TTGame_Test();

	/**
     *  Processes button presses of the players in the game field.
     */
    void OnFieldButtonPressed();

    /**
     * Processes button press of the start game button.
     */
	void OnStartGamePressed();

    /**
     *
     * Processes button press of the reset game button.
     */
	void OnResetButtonPressed();

    /**
     * Resets the game to initial state
     */
    void InitializeGameRound();

    /**
     * Initializes the result matrix components to the value of 100 so that the win sum for each player is unique.
     */
    void InitializeResultMatrix();

    /**
     * Determines if the last set button has lead for the current player to win the game.
     *
     * @param pressedPushButton the button that was last pressed.
     * @return true if player is a winner false otherwise.
     */
    bool DidPlayerWinner(const class QPushButton& pressedPushButton);

    QPushButton& GetFieldButton(const int fieldButtonIndex)
    {
		return *super::fieldButtons[fieldButtonIndex];
    }

private:
	using super = TTTGame;
};

#endif // TTGAME_TEST_H

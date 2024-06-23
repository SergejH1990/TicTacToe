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
	void OnGameButtonPressed();
	void OnStartGamePressed();
	void OnResetButtonPressed();
	void ResetButtons();
	bool IsWinner(const class QPushButton& checkedPushButton);

	class QLabel* playerTurnLabel;
	class QLabel* scoreLabel;

	class QPushButton* startButton;
	class QPushButton* resetButton;

	class QGridLayout* gameLayout;
	class QVBoxLayout* mainLayout;

	std::array<class QPushButton*, 9> gameButtons;

	int xWins;
	int oWins;
	int turns;
	bool isGameInProgress;
	bool isXTurn;

private:
	using super = QWidget;
};

#endif // TTTGAME_H

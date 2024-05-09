#ifndef TTTGAME_H
#define TTTGAME_H

#include <QWidget>

class TTTGame : public QWidget
{
    Q_OBJECT
public:
    explicit TTTGame(QWidget *parent = nullptr);
    virtual ~TTTGame();

    void paintField();
    void resetFields();
    void animateButton();

protected:
    class QPushButton* topLeftButton;
    class QPushButton* topMiddleButton;
    class QPushButton* topRightButton;
    class QPushButton* centerLeftButton;
    class QPushButton* centerMiddleButton;
    class QPushButton* centerRightButton;
    class QPushButton* bottomLeftButton;
    class QPushButton* bottomMiddleButton;
    class QPushButton* bottomRightBUtton;

    class QLabel* winnerLabel;
    class QLabel* playerTurnLabel;

    class QPushButton* startButton;
    class QPushButton* resetButton;
    class QPushButton* XButton;
    class QPushButton* OButton;

    class QGridLayout* gameLayout;
    class QVBoxLayout* mainLayout;

private:
    using super = QWidget;

};




#endif // TTTGAME_H

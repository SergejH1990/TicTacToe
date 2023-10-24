#ifndef TTTGAME_H
#define TTTGAME_H

#include <QWidget>
#include <QPropertyAnimation>

class TTTGame : public QWidget
{
    Q_OBJECT
public:
    TTTGame(QWidget *parent = nullptr);
    ~TTTGame();

    void paintField();
    void resetFields();
    void animateButton();

protected:
    class QPushButton* topLeftButton;
    class QPushButton* topMIddleButton;
    class QPushButton* topRightButton;
    class QPushButton* centerLeftButton;
    class QPushButton* centerMiddleButton;
    class QPushButton* centerRightButton;
    class QPushButton* bottomLeftButton;
    class QPushButton* bottomMiddleButton;
    class QPushButton* bottomRightBUtton;

    class QPushButton* startButton;
    class QPushButton* resetButton;
    class QPushButton* XButton;
    class QPushButton* OButton;

    class QGridLayout* gameLayout;
    class QHBoxLayout* mainLayout;

private:
    using super = QWidget;

};




#endif // TTTGAME_H

#ifndef TTTGAME_H
#define TTTGAME_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class TTTGame; }
QT_END_NAMESPACE

class TTTGame : public QWidget
{
    Q_OBJECT

public:
    TTTGame(QWidget *parent = nullptr);
    ~TTTGame();

private:
    Ui::TTTGame *ui;
};
#endif // TTTGAME_H

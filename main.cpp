#include "tttgame.h"

#include <QApplication>
#include <QPropertyAnimation>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TTTGame w;

    w.show();
    return a.exec();
}

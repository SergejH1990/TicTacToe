#include "tttgame.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TTTGame w;
    w.show();
    return a.exec();
}

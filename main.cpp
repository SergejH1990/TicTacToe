#include "tttgame.h"

#include <QApplication>
#include <QDebug>
#include <QFile>

int main(int argc, char *argv[])
{
	QApplication application(argc, argv);

	QFile styleSheetFile(":/Resources/style.qss");
	if (styleSheetFile.open(QFile::ReadOnly))
	{
		qDebug() << "File loaded successfully";
		qApp->setStyleSheet(QLatin1String(styleSheetFile.readAll()));
	}

	TTTGame ticTacToe;
	ticTacToe.show();

	return application.exec();
}

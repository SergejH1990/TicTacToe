
#include <QTcpSocket>

#include "tttNetworkManager.h"

using namespace Network;

TTTNetworkManager::TTTNetworkManager(QObject *parent):
super(parent),
gameSocket(nullptr)
{
	gameSocket = new QTcpSocket(this);
	gameSocket->connectToHost(QHostAddress::LocalHost, 8080);
	gameSocket->open(QIODevice::ReadWrite);

	if (gameSocket->isOpen())
	{
		qDebug() << "Connected Socket";
	}
	else
	{
		qDebug() << "Connected Failed";
	}
}

TTTNetworkManager::~TTTNetworkManager()
{
}

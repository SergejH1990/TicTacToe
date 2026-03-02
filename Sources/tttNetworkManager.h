#ifndef TTTNETWORKMANAGER_H
#define TTTNETWORKMANAGER_H

#include <QObject>

namespace Network {

	class TTTNetworkManager : public QObject
	{
		Q_OBJECT
	public:
		explicit TTTNetworkManager(QObject *parent = nullptr);
		virtual ~TTTNetworkManager();

	protected:
		class QTcpSocket* gameSocket;

	private:
		using super = QObject;
	};
}

#endif // TTTNETWORKMANAGER_H

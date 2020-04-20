#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QDebug>
#include <QHostAddress>
#include <QTcpSocket>
#include "tcpsocket.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server(QObject *parent = 0, quint16 port = 520);
    ~Server();

signals:
    void updateMsg(QByteArray datagram);

public slots:
    void sendMSG(QString);
    void acceptConfig(QString ,int);

private slots:
    void slotAccept();

    void slotReadData();

    void slotDisconnected(int socketDescrip);


    void slotUpdate(QByteArray datagram);

protected:
   virtual void incomingConnection(qintptr socket);

private:
    QList<TcpSocket *> clients;
    TcpSocket *client;
};

#endif // SERVER_H

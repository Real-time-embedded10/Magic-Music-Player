#include "server.h"
#include <QDebug>

Server::Server(QObject *parent, quint16 port) : QTcpServer(parent)
{

}

Server::~Server()
{

}

void Server::sendMSG(QString buf)
{
    foreach (TcpSocket *c, clients) {
        qDebug()<<"ddd";
        c->write(buf.toLatin1());
    }
}

void Server::acceptConfig(QString ip, int port)
{
    bool ret = listen(QHostAddress(ip), port);
    if(ret == true){
        qDebug()<<"listen ok";
    }
    connect(this, SIGNAL(newConnection()), SLOT(slotAccept()));
}

void Server::slotAccept()
{  
    qDebug() << "newConnection";
}

void Server::slotReadData()
{
    qDebug()<<"";
}

void Server::incomingConnection(qintptr socket)
{
    qDebug() << "incomingConnection";
    client = new TcpSocket();
    client->setSocketDescriptor(socket);

    connect(client, SIGNAL(readyRead()),this, SLOT(slotReadData()));
    connect(client, SIGNAL(disconnected(int)),
            this, SLOT(slotDisconnected(int)));
    connect(client, SIGNAL(updateMsg(QByteArray)),
            this, SLOT(slotUpdate(QByteArray)));

    clients << client;
}

void Server::slotDisconnected(int socketDescrip)
{
    qDebug() << "disconnect client : " << socketDescrip;
    foreach (TcpSocket *c, clients) {
        if(c->socketDescriptor() == socketDescrip)
            clients.removeOne(c);
        return;
    }
}

void Server::slotUpdate(QByteArray datagram)
{
     emit updateMsg(datagram);

//    foreach (TcpSocket *c, clients) {
//        c->write(datagram);
//    }

}

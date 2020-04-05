#include "tcpsocket.h"

TcpSocket::TcpSocket(QObject *parent):QTcpSocket(parent)
{
    connect(this, SIGNAL(disconnected()), SLOT(slotDisconnected()));
    connect(this, SIGNAL(readyRead()), SLOT(slotReadData()));
}

TcpSocket::~TcpSocket()
{

}

void TcpSocket::slotDisconnected()
{
    emit disconnected(socketDescriptor());
}

void TcpSocket::slotReadData()
{
    while(bytesAvailable() > 0){
        QByteArray datagrame;
        datagrame.resize(bytesAvailable());
        read(datagrame.data(), datagrame.size());
        emit updateMsg(datagrame);
    }
}

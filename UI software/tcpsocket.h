#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QObject>
#include <QTcpSocket>

class TcpSocket : public QTcpSocket
{
    Q_OBJECT

public:
    TcpSocket(QObject *parent = 0);
    ~TcpSocket();

signals:
    void disconnected(int socket);

    void updateMsg(QByteArray ba);

private slots:
    void slotDisconnected();

    void slotReadData();
};

#endif // TCPSOCKET_H

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QtNetwork>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QDateTime>
#include "qmpuobject.h"
#include <QThread>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

signals:
    void sendStartMpu();
    void sendStopMpu();

public slots:
    void readData();
    void ReadError(QAbstractSocket::SocketError);
    void acceptMpuData(QString);

private slots:
    void on_pushButton_a_clicked();
    void on_pushButton_b_clicked();
    void on_pushButton_d_clicked();
    void on_pushButton_e_clicked();
    void on_pushButton_f_clicked();
    void on_pushButton_g_clicked();
    void on_pushConnect_clicked();

    void on_pushButton_h_clicked();

    void on_pushButton_i_clicked();

private:
    Ui::MainWidget *ui;
    QTcpSocket * tcpClient;

    QMpuObject *m_QMpuObject;
    QThread workThread;
};

#endif // MAINWIDGET_H

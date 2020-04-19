#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QtNetwork>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QDateTime>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
public slots:
        void readData();
    void ReadError(QAbstractSocket::SocketError);


private slots:

    void on_pushConnect_clicked();

    void on_pushButton_a_clicked();

    void on_pushButton_b_clicked();

    void on_pushButton_c_clicked();

    void on_pushButton_d_clicked();

    void on_pushButton_e_clicked();

    void on_pushButton_f_clicked();

    void on_pushButton_g_clicked();

private:
    Ui::MainWidget *ui;
       QTcpSocket * tcpClient;
};

#endif // MAINWIDGET_H

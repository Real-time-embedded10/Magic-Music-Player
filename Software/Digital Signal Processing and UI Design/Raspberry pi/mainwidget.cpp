#pragma execution_character_set("utf-8")
#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
        ui->setupUi(this);
    tcpClient = new QTcpSocket(this);

    ui->txtIp->setText("127.0.0.1");
    ui->txtPort->setText("520");

    tcpClient->abort();
    connect(tcpClient,SIGNAL(readyRead()),this,SLOT(readData()));
    connect(tcpClient,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(ReadError(QAbstractSocket::SocketError)));


}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::readData()
{
    tcpClient->disconnectFromHost();
    ui->pushConnect->setText("连接");
    this->ui->txtIp->setEnabled(true);
    this->ui->txtPort->setEnabled(true);
}

void MainWidget::ReadError(QAbstractSocket::SocketError)
{
    tcpClient->disconnectFromHost();
}

void MainWidget::on_pushConnect_clicked()
{
    qDebug() << "点击连接：" ;
      if ("连接" == this->ui->pushConnect->text())
      {
          QString ipAdd(this->ui->txtIp->text()), portd(this->ui->txtPort->text());
          if (ipAdd.isEmpty() || portd.isEmpty())
          {
              return;
          }
          tcpClient->connectToHost(ipAdd,portd.toInt());
          if (tcpClient->waitForConnected(1000))
          {
              ui->pushConnect->setText("断开");
              this->ui->txtIp->setEnabled(false);
              this->ui->txtPort->setEnabled(false);
          }
      }
      else
      {
          tcpClient->disconnectFromHost();
          if (tcpClient->state() == QAbstractSocket::UnconnectedState || tcpClient->waitForDisconnected(1000) )
          {
              ui->pushConnect->setText("连接");
              this->ui->txtIp->setEnabled(true);
              this->ui->txtPort->setEnabled(true);
          }
      }
}

void MainWidget::on_pushButton_a_clicked()
{
    QString data = "1";
    if (data.isEmpty())
    {
        return ;
    }
    tcpClient->write(data.toUtf8());
}

void MainWidget::on_pushButton_b_clicked()
{
    QString data = "2";
    if (data.isEmpty())
    {
        return ;
    }
    tcpClient->write(data.toUtf8());
}

void MainWidget::on_pushButton_c_clicked()
{
    QString data = "3";
    if (data.isEmpty())
    {
        return ;
    }
    tcpClient->write(data.toUtf8());
}

void MainWidget::on_pushButton_d_clicked()
{
    QString data = "4";
    if (data.isEmpty())
    {
        return ;
    }
    tcpClient->write(data.toUtf8());
}

void MainWidget::on_pushButton_e_clicked()
{
    QString data = "5";
    if (data.isEmpty())
    {
        return ;
    }
    tcpClient->write(data.toUtf8());
}

void MainWidget::on_pushButton_f_clicked()
{
    QString data = "6";
    if (data.isEmpty())
    {
        return ;
    }
    tcpClient->write(data.toUtf8());
}

void MainWidget::on_pushButton_g_clicked()
{
    QString data = "7";
    if (data.isEmpty())
    {
        return ;
    }
    tcpClient->write(data.toUtf8());
}

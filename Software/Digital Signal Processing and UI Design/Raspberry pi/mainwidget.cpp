#pragma execution_character_set("utf-8")
#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    tcpClient = new QTcpSocket(this);

    ui->txtIp->setText("192.168.1.104");
    ui->txtPort->setText("520");

    tcpClient->abort();
    connect(tcpClient,SIGNAL(readyRead()),this,SLOT(readData()));
    connect(tcpClient,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(ReadError(QAbstractSocket::SocketError)));

   m_QMpuObject = new QMpuObject();
   m_QMpuObject->moveToThread(&workThread);
    connect(&workThread, &QThread::finished, m_QMpuObject, &QObject::deleteLater);
    connect(this,SIGNAL(sendStartMpu()),m_QMpuObject,SLOT(acceptStartMpu()));
    connect(this,SIGNAL(sendStopMpu()),m_QMpuObject,SLOT(acceptStopMpu()));

  connect(m_QMpuObject,SIGNAL(sendMpuData(QString)),this,SLOT(acceptMpuData(QString)));
        workThread.start();

}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::readData()
{
    tcpClient->disconnectFromHost();
    ui->pushConnect->setText("Connect");
    this->ui->txtIp->setEnabled(true);
    this->ui->txtPort->setEnabled(true);
}

void MainWidget::ReadError(QAbstractSocket::SocketError)
{
    tcpClient->disconnectFromHost();
}

void MainWidget::acceptMpuData(QString srr)
{
    if(srr == "1"){
        QString data = "1";
        tcpClient->write(data.toUtf8());
    }else if(srr == "2"){
        QString data = "2";
        tcpClient->write(data.toUtf8());
    }else if(srr == "3"){
        QString data = "3";
        tcpClient->write(data.toUtf8());
    }else if(srr == "4"){
        QString data = "4";
        tcpClient->write(data.toUtf8());
    }else if(srr == "5"){
        QString data = "5";
        tcpClient->write(data.toUtf8());
    }else if(srr == "6"){
        QString data = "6";
        tcpClient->write(data.toUtf8());
    }else if(srr == "7"){
        QString data = "7";
        tcpClient->write(data.toUtf8());
    }else if(srr == "8"){
        QString data = "8";
        tcpClient->write(data.toUtf8());
    }
}

void MainWidget::on_pushConnect_clicked()
{
    qDebug() << "pushConnect：" ;
    if ("Connect" == this->ui->pushConnect->text())
    {
        QString ipAdd(this->ui->txtIp->text()), portd(this->ui->txtPort->text());
        if (ipAdd.isEmpty() || portd.isEmpty())
        {
            return;
        }
        tcpClient->connectToHost(ipAdd,portd.toInt());
        if (tcpClient->waitForConnected(1000))
        {
            emit sendStartMpu();
            ui->pushConnect->setText("DisConnect");
            this->ui->txtIp->setEnabled(false);
            this->ui->txtPort->setEnabled(false);
        }
    }
    else
    {
        tcpClient->disconnectFromHost();
        if (tcpClient->state() == QAbstractSocket::UnconnectedState || tcpClient->waitForDisconnected(1000) )
        {
            emit sendStopMpu();
            ui->pushConnect->setText("Connect");
            this->ui->txtIp->setEnabled(true);
            this->ui->txtPort->setEnabled(true);
        }
    }
}

void MainWidget::on_pushButton_a_clicked()
{
    QString data = "7";
    if (data.isEmpty())
    {
        return ;
    }
    tcpClient->write(data.toUtf8());
}

void MainWidget::on_pushButton_b_clicked()
{
    QString data = "8";
    if (data.isEmpty())
    {
        return ;
    }
    tcpClient->write(data.toUtf8());
}

void MainWidget::on_pushButton_c_clicked()
{
    QString data = "1";
    if (data.isEmpty())
    {
        return ;
    }
    tcpClient->write(data.toUtf8());
}

void MainWidget::on_pushButton_d_clicked()
{
    QString data = "2";
    if (data.isEmpty())
    {
        return ;
    }
    tcpClient->write(data.toUtf8());
}

void MainWidget::on_pushButton_e_clicked()
{
    QString data = "3";
    if (data.isEmpty())
    {
        return ;
    }
    tcpClient->write(data.toUtf8());
}

void MainWidget::on_pushButton_f_clicked()
{
    QString data = "4";
    if (data.isEmpty())
    {
        return ;
    }
    tcpClient->write(data.toUtf8());
}

void MainWidget::on_pushButton_g_clicked()
{
    QString data = "5";
    if (data.isEmpty())
    {
        return ;
    }
    tcpClient->write(data.toUtf8());
}

void MainWidget::on_pushButton_h_clicked()
{
    QString data = "6";
    if (data.isEmpty())
    {
        return ;
    }
    tcpClient->write(data.toUtf8());
}

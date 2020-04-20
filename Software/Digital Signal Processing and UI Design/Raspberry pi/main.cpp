#pragma execution_character_set("utf-8")
#include "mainwidget.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QTextCodec>
#include <QProcess>
#include <QFontDatabase>
#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QIcon>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    //    initDebug();
    //    qInstallMessageHandler(outputMessage);
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
#if _MSC_VER
    QTextCodec *codec = QTextCodec::codecForName("gbk");
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
#endif
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
#endif
    a.setWindowIcon(QIcon(":/main.ico"));

    QString qssFile = ":/qss/darkblue.css";
    QFile file(qssFile);

    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }
    QString starttime = "2020-03-16 12:00:01";
    QString endtime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QDateTime start = QDateTime::fromString(starttime, "yyyy-MM-dd hh:mm:ss");
    QDateTime end = QDateTime::fromString(endtime, "yyyy-MM-dd hh:mm:ss");
    uint stime = start.toTime_t();
    uint etime = end.toTime_t();
    int ndaysec = 24*60*60;
    MainWidget w;
    w.setWindowTitle("MPU");
    int day = (etime - stime)/(ndaysec) + ((etime - stime)%(ndaysec)+(ndaysec-1))/(ndaysec) - 1;
    qDebug() << "Day ---------------------------------------------------- " << day;
//    if(day > 500){
//        QMessageBox::critical(nullptr, "Error", QString("Fail to start the project, please contact the developer!"));
//    }else{
        w.show();
//    }
    return a.exec();
}

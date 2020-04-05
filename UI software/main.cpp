#pragma execution_character_set("utf-8")
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
#include "player.h"
#include "mediacenter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
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
    a.setApplicationDisplayName("");
    QString qssFile = ":/qss/darkblue.css";
    QFile file(qssFile);
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }
    Player player;
#if defined(Q_WS_SIMULATOR)
    player.setAttribute(Qt::WA_LockLandscapeOrientation);
    player.showMaximized();
#else
    player.show();
#endif
    return a.exec();
}

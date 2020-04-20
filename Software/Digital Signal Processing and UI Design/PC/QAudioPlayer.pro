TEMPLATE = app
TARGET = QAudioPlayer
QT += multimedia \
      multimediawidgets \
      widgets \
      sql
QT       += core gui network

DESTDIR = $$PWD/bin
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS = \
    player.h \
    playercontrolsl.h \
    playlistmodel.h \
    server.h \
    tcpsocket.h \
    videowidgetl.h \
    mediacenter.h \
    connection.h
SOURCES = main.cpp \
    player.cpp \
    playercontrolsl.cpp \
    playlistmodel.cpp \
    server.cpp \
    tcpsocket.cpp \
    videowidgetl.cpp \
    mediacenter.cpp \
    connection.cpp

maemo* {
    DEFINES += PLAYER_NO_COLOROPTIONS
}

RESOURCES += \
    other/qss.qrc \
    other/main.qrc
win32:RC_FILE   = other/main.rc

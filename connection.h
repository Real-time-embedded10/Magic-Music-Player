#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QSqlDatabase>
#include <QtSql>
#include <QMap>
#include <QList>

class Connection : public QObject
{
    Q_OBJECT
public:
    explicit Connection(QObject *parent = 0);
    void createTables();
    bool insertMusic(QMap<QString,QString> map);
    QStringList getKeys(QString key);
    QList<QMap<QString,QString> > search(QString inf,QString key);
    QList<QMap<QString,QString> > map();
    void deletMusic(QString i);
    ~Connection();
signals:

public slots:
private:
    QSqlDatabase db;
    QString errMsg;
};

#endif // CONNECTION_H

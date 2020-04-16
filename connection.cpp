#include "connection.h"
#include <QDebug>
#include <QDateTime>
#include <QMap>
#include <assert.h>

Connection::Connection(QObject *parent) :
    QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("media.db");

    if(db.open())
        createTables();
    else
        errMsg = "Can't open db";
}

void Connection::createTables()
{
    QSqlQuery query(db);
    if(!query.exec("select * from musicgroup;"))
    {
        qDebug()<<"Do not have db";
        assert(query.exec("create table musicgroup(id integer primary key,groupname text);"));
        assert(query.exec("create table music(id integer primary key,musicname text, albumname text,albumpicpath text,composer text,adddate text,singer text,url text NOT NULL unique,lrc text);"));
        assert(query.exec("create table playlist(groupid integer,musicid integer,foreign key(groupid) references musicgroup(id),foreign key(musicid) references music(id))"));
    }
    else
    {
        qDebug()<<"Aready have db";
    }
 }


bool Connection::insertMusic(QMap<QString,QString> map)
{
    QSqlQuery query(db);
    query.exec("select max(id) from music");
    if(query.next())
    {
        int id = query.value("max(id)").toInt();id++;qDebug()<<id;
        map["id"]==""?id=id:id=map["id"].toInt();
        QDateTime dt;
        QTime time;
        QDate date;
        dt.setTime(time.currentTime());
        dt.setDate(date.currentDate());

        QString sql ="insert into music(id,musicname,albumname,albumpicpath,composer,adddate,singer,url,lrc) values('"+QString::number(id,10)+"','"+map["musicname"]+"','"+map["albumname"]+"','"+map["albumpicpath"]+"','"+map["composer"]+"','"+dt.toString("yyyy:MM:dd:hh:mm:ss")+"','"+map["singer"]+"','"+map["url"]+"','"+map["lrc"]+"')";
        qDebug()<<sql;

        QSqlQuery insert(db);
        if(insert.exec(sql))
                return true;
        else
            throw QString("Please don't add the same music!");
    }
    throw QString ("FATAL DB BUG!");
    return false;
}

QStringList Connection::getKeys(QString key)
{
    QStringList list;
    QSqlQuery query(db);
    if(key == "groupname")
    {
        QString str = "SELECT distinct "+key+" FROM musicgroup";
        query.exec(str);
        while(query.next())
        {
            list.append(query.value(0).toString());
        }
        return list;
    }
    else if(key == "adddate")
    {
        QString str = "SELECT distinct substr("+key+",1,10) FROM music";
        query.exec(str);
        while(query.next())
        {
            list.append(query.value(0).toString());
        }
        return list;
    }
    else
    {
        QString str = "SELECT distinct "+key+" FROM music";
        query.exec(str);
        while(query.next())
        {
            list.append(query.value(0).toString());
        }
        return list;
    }
}

QList<QMap<QString,QString> > Connection::search(QString inf,QString key)
{
    QSqlQuery query;
    QString str = (key == "musicgroup")?"select * "
                                        "from music,playlist,musicgroup "
                                        "where musicgroup.id=playlist.groupid and music.id=playlist.musicid "
                                        "and musicgroup.groupname='"+inf+"'":"select * "
                                        "from music where "+key+" like '%"+inf+"%'";
    query.exec(str);
    qDebug()<<str;
    QList< QMap<QString,QString> > list;
    while(query.next())
    {
        QMap<QString,QString> map;
        map["id"]=query.value("id").toString();
        map["musicname"]=query.value("musicname").toString();
        map["albumname"]=query.value("albumname").toString();
        map["albumpicpath"]=query.value("albumpicpath").toString();
        map["composer"]=query.value("composer").toString();
        map["adddate"]=query.value("adddate").toString();
        map["singer"]=query.value("singer").toString();
        map["url"]=query.value("url").toString();
        map["lrc"]=query.value("lrc").toString();
        list.append(map);
    }
    return list;
}

QList<QMap<QString,QString> >  Connection::map()
{
    QSqlQuery query;
    query.exec("select * from music");
    qDebug()<<"select * from music";
    QList< QMap<QString,QString> > list;
    while(query.next())
    {
        QMap<QString,QString> map;
        map["id"]=query.value("id").toString();
        map["musicname"]=query.value("musicname").toString();
        map["albumname"]=query.value("albumname").toString();
        map["albumpicpath"]=query.value("albumpicpath").toString();
        map["composer"]=query.value("composer").toString();
        map["adddate"]=query.value("adddate").toString();
        map["singer"]=query.value("singer").toString();
        map["url"]=query.value("url").toString();
        qDebug()<<map["url"];
        map["lrc"]=query.value("lrc").toString();
        list.append(map);
    }
    return list;
}

Connection::~Connection()
{
    db.close();
    qDebug()<<"db closed";
}

void Connection::deletMusic(QString i)
{
    QSqlQuery query(db);
       QString str = "delete from music where id="+i;
       if(query.exec(str))
       {
           return;
       }
       else
       {
           query.clear();
           QString str = "delete from playlist where musicid = "+i;
           query.exec(str);
           query.clear();
           QString stri = "delete from music where id="+i;
           query.exec(stri);
       }
}

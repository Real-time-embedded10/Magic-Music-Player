#include "mediacenter.h"

#include <QLayout>
#include <QRadioButton>
#include <QTableWidget>
#include <QContextMenuEvent>
#include <QMenu>
#include <QPoint>
#include "connection.h"

MediaCenter::MediaCenter(QWidget *parent) :
    QWidget(parent)
  ,album(0)
  ,singer(0)
  ,adddate(0)
  ,musicgroup(0)
{
    album = new QComboBox;
    singer = new QComboBox;
    adddate = new QComboBox;
    musicgroup = new QComboBox;
    search = new QLineEdit;
    search->setFixedWidth(100);
    s_btn = new QPushButton(tr("search"));
    mainlayout = new QVBoxLayout();
    QRadioButton *rsinger= new QRadioButton(tr("singer"));
    QRadioButton *ralbum= new QRadioButton(tr("album"));
    QRadioButton *rdate= new QRadioButton(tr("date"));
    QRadioButton *rgroup= new QRadioButton(tr("group"));
    QRadioButton *rsearch = new QRadioButton(tr("search"));
    singer->setEnabled(false);
    album->setEnabled(false);
    adddate->setEnabled(false);
    musicgroup->setEnabled(false);
    search->setEnabled(false);
    QGridLayout *layout = new QGridLayout;
    layout->setMargin(0);
    layout->addWidget((QAbstractButton*)rsinger,0,0);
    layout->addWidget(singer,0,1);
    layout->addWidget((QAbstractButton*)ralbum,0,2);
    layout->addWidget(album,0,3);
    layout->addWidget((QAbstractButton*)rdate,1,0);
    layout->addWidget(adddate,1,1);
    layout->addWidget((QAbstractButton*)rgroup,1,2);
    layout->addWidget(musicgroup,1,3);
    layout->addWidget((QAbstractButton*)rsearch,2,0);
    layout->addWidget(search,2,1);
    layout->addWidget(s_btn,2,3);
    table = new QTableWidget;
    table->setColumnCount(8);
    table->setRowCount(100);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setContextMenuPolicy(Qt::CustomContextMenu);
    popMenu = new QMenu(table);
    del = new QAction(tr("delete"),this);
    add = new QAction(tr("add to list"),this);
    mainlayout->addLayout(layout);
    mainlayout->addWidget((QWidget*)table);
    setLayout(mainlayout);
    QObject::connect(rsinger,SIGNAL(toggled(bool)),singer,SLOT(setEnabled(bool)));
    QObject::connect(rdate,SIGNAL(toggled(bool)),adddate,SLOT(setEnabled(bool)));
    QObject::connect(rgroup,SIGNAL(toggled(bool)),musicgroup,SLOT(setEnabled(bool)));
    QObject::connect(ralbum,SIGNAL(toggled(bool)),album,SLOT(setEnabled(bool)));
    QObject::connect(rsearch,SIGNAL(toggled(bool)),search,SLOT(setEnabled(bool)));
    initial();
    connect(s_btn,SIGNAL(clicked()),this,SLOT(Search()));
    connect(table,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(customContextMenuRequested(QPoint)));
    connect(add,SIGNAL(triggered()),this,SLOT(addTolist()));
    connect(del,SIGNAL(triggered()),this,SLOT(delfromdb()));


}

void MediaCenter::initial()
{
    album->clear();
    singer->clear();
    adddate->clear();
    musicgroup->clear();
    album->addItems(getItems("albumname"));
    singer->addItems(getItems("singer"));
    adddate->addItems(getItems("adddate"));
    musicgroup->addItems(getItems("musicgroup"));
    setItems((new Connection)->map());
}

void MediaCenter::setUnable()
{
}

QStringList MediaCenter::getItems(QString key)
{
    qDebug()<<key;
    Connection *con = new Connection();
    return con->getKeys(key);
}
void MediaCenter::setItems(QList<QMap<QString, QString> > lists)
{
    table->clear();
    int i = 0;
    QMap<QString,QString> map;
    foreach (map, lists) {
        table->setItem(i,0,new QTableWidgetItem(map["id"]));
        table->setItem(i,1,new QTableWidgetItem(map["musicname"]));
        table->setItem(i,2,new QTableWidgetItem(map["singer"]));
        table->setItem(i,3,new QTableWidgetItem(map["composer"]));
        table->setItem(i,4,new QTableWidgetItem(map["albumname"]));
        table->setItem(i,5,new QTableWidgetItem(map["adddate"]));
        table->setItem(i,6,new QTableWidgetItem(map["lrc"]));
        table->setItem(i,7,new QTableWidgetItem(map["url"]));
        qDebug()<<map["musicname"];
        i++;
    }
    QStringList headers;
    headers<<tr("id")<<tr("name")<<tr("singer")<<tr("composer")<<tr("album")<<tr("date")<<tr("lrc")<<tr("url");
    foreach (QString str, headers) {
        qDebug()<<str<<" ok";
    }
    table->setHorizontalHeaderLabels(headers);
}

void MediaCenter::Search()
{
    QString key="";
    QString inf="";
    if(album->isEnabled())
    {
        key = "albumname";
        inf = album->currentText();
    }
    else if(singer->isEnabled())
    {
        key  = "singer";
        inf = singer->currentText();
    }
    else if(adddate->isEnabled())
    {
        key = "adddate";
        inf = adddate->currentText();
    }
    else if(musicgroup->isEnabled())
    {
        key = "musicgroup";
        inf = musicgroup->currentText();
    }
    else if(search->isEnabled())
    {
        key = "musicname";
        inf = search->text();
    }
    setItems((new Connection)->search(inf,key));
}

void MediaCenter::RightClickedOperation()
{

}

void MediaCenter::customContextMenuRequested(QPoint)
{
    popMenu->addAction(add);
    popMenu->addAction(del);
    popMenu->exec(QCursor::pos());
}

MediaCenter::~MediaCenter()
{

}

void MediaCenter::addTolist()
{
    int row =  table->currentRow();
    QTableWidgetItem *item = table->item(row,7);
    qDebug()<<"clickeed"<<item->text();
    list.append(item->text());
    sendtoplayer();
}

void MediaCenter::delfromdb()
{
    int row =  table->currentRow();
    QTableWidgetItem *item = table->item(row,0);
    qDebug()<<"clickeed"<<item->text();
    (new Connection)->deletMusic(item->text());
    setItems((new Connection)->map());
}

QStringList MediaCenter::getlist()
{
    return list;
}

void MediaCenter::setItems()
{
    list.clear();
}

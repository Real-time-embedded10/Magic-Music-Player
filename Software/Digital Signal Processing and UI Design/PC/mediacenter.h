#ifndef MEDIACENTER_H
#define MEDIACENTER_H

#include <QWidget>
#include <QTableWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QBoxLayout>
#include <stdlib.h>
#include <string.h>
namespace Ui {
class MediaCenter;
}

class MediaCenter : public QWidget
{
    Q_OBJECT

public:
    explicit MediaCenter(QWidget *parent = 0);
    ~MediaCenter();
    void setItems(QList<QMap<QString,QString> > lists);
    QList<QMap<QString,QString> > searchByInf(QString inf);
    QStringList getItems(QString key);
    void setItems();

public slots:
    void Search();
    void RightClickedOperation();
    void customContextMenuRequested(QPoint);
    void addTolist();
    void delfromdb();
    void initial();
    void setUnable();
    QStringList getlist();

signals:
    void sendtoplayer();
private:
    QTableWidget *table;
    QComboBox  *album;
    QComboBox *singer;
    QComboBox *adddate;
    QComboBox *musicgroup;
    QLineEdit *search;
    QPushButton *s_btn;

    QMenu *popMenu;
    QAction *del;
    QAction *add;

    QStringList list;

    QBoxLayout *mainlayout;
};

#endif // MEDIACENTER_H

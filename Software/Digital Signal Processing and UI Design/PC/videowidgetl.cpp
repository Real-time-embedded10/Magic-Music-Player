
#include "videowidgetl.h"

#include <QKeyEvent>
#include <QMouseEvent>

VideoWidgetL::VideoWidgetL(QWidget *parent)
    : QVideoWidget(parent)
{
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    QPalette p = palette();
    p.setColor(QPalette::Window, Qt::black);
    setPalette(p);

    setAttribute(Qt::WA_OpaquePaintEvent);
}

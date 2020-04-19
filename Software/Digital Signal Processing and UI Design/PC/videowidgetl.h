
#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QVideoWidget>

class VideoWidgetL : public QVideoWidget
{
    Q_OBJECT

public:
    VideoWidgetL(QWidget *parent = 0);
};

#endif // VIDEOWIDGET_H

#ifndef QMPUOBJECT_H
#define QMPUOBJECT_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QDebug>
#include <iostream>
#include "MPU6050_Types.h"
#include "MPU6050.h"
#include "Segmentation.h"
#include "FeatureExtraction.h"
#include "Classification.h"

class QMpuObject : public QObject
{
    Q_OBJECT
public:
    explicit QMpuObject(QObject *parent = nullptr);

signals:
    void sendMpuData(QString);

public slots:
    void acceptStartMpu();
    void acceptStopMpu();
    void acceptTimeout();

private:
    QTimer *m_timer;
    MPU6050_SENSOR *imu;
    SEGMENTATION seg;
    FEATUREEXTRACTION fea;
    CLASSIFICATION cla;
    float xg, yg, zg;
    float xa, ya, za;
    float temp;
    uint32_t sample_count = 0;
  

};

#endif // QMPUOBJECT_H

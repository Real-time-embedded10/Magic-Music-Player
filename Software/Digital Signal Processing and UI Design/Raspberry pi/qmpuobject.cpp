#include "qmpuobject.h"

void self_test_all_range(MPU6050_SENSOR imu) {
    float differences[6];
    for (uint8_t gyro_range = 0x00; gyro_range < 0x04; ++gyro_range) {
        for (uint8_t accel_range = 0x00; accel_range < 0x04; ++accel_range) {
            imu.selfTest(gyro_range, accel_range, differences);
            std::cout << "gyroscope range: " << std::hex << (int)gyro_range << std::endl;
            std::cout << "accelerometer range: " << std::hex << (int)accel_range << std::endl;
            for (int i = 0; i < 6; ++i) {
                std::cout << differences[i] << "%" << std::endl;
            }
        }
    }
}

QMpuObject::QMpuObject(QObject *parent) : QObject(parent)
{
    m_timer = NULL;
    imu = NULL;
}

void QMpuObject::acceptStartMpu()
{
    qDebug()<<"acceptStartMpu";
      //  imu = new MPU6050_SENSOR(MPU6050_DEFAULT_ADDRESS);
    //    imu->initialize(50, 0x03, 0x00, 0x03, 0x01);

//    m_timer = new QTimer;
//    connect(m_timer,SIGNAL(timeout()),this,SLOT(acceptTimeout()));
    // m_timer->start(50);

}

void QMpuObject::acceptStopMpu()
{
    if(m_timer != NULL){
        m_timer->stop();
        delete m_timer;
        m_timer = NULL;
    }
    if(imu ==NULL ){
        imu->setSleep();
    }
}

void QMpuObject::acceptTimeout()
{
    // self test
    //  self_test_all_range(imu);
    // initialize

    sample_count += 1;
    imu->getGyroData(&xg, &yg, &zg);
    imu->getAccelData(&xa, &ya, &za);
    imu->getTempData(&temp);
    seg.SegmentationProcess(xa, ya, za, xg, yg, zg);
    if (seg.GestureDetectResult == 1) {
        std::cout << "YES" << std::endl;
        fea.extractionProcess(seg.recordTargetXA, seg.recordTargetYA, seg.recordTargetZA, seg.recordTargetXG, seg.recordTargetYG, seg.recordTargetZG);
        cla.classify(fea.extractedFeature);
        std::cout << cla.classificationResult << std::endl;

        //Transmit corresopding signal according to the classificationResult
        //emit sendMpuData("1");//Previous
        //emit sendMpuData("2");//Next
        //emit sendMpuData("3");//Volume++
        //emit sendMpuData("4");//Volume--
        //emit sendMpuData("5");//Speed++
        //emit sendMpuData("6");//Speed--

    }
    //         std::cout << seg.GestureDetectResult<< "%00" << std::endl;
}

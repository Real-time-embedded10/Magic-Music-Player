#ifndef _MPU6050_H_
#define _MPU6050_H_

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <iostream>
#include <cmath>
#include "MPU6050_Registers.h"
#include "MPU6050_Types.h"


class MPU6050_SENSOR {
public:
    MPU6050_SENSOR(uint8_t);
    uint8_t getSampleRateDivider();
    void setSampleRateDivider(uint8_t);
    unsigned int getSampleRate();
    void setSampleRate(unsigned int);
    uint8_t getDLPFConfig();
    void setDLPFConfig(uint8_t);
    uint8_t getFullScaleGyroRange();
    void setFullScaleGyroRange(uint8_t);
    uint8_t getFullScaleAccelRange();
    void setFullScaleAccelRange(uint8_t);
    void getAccelRawData(int16_t*, int16_t*, int16_t*);
    void getAccelData(float*, float*, float*);
    void getGyroRawData(int16_t*, int16_t*, int16_t*);
    void getGyroData(float*, float*, float*);
    void getTempRawData(int16_t*);
    void getTempData(float*);
    void resetGyroSignalPath();
    void resetAccelSignalPath();
    void resetTempSignalPath();
    void resetAllSignalPath();
    bool getFIFOEnabled();
    void setFIFOEnabled();
    void setFIFODisabled();
    void resetFIFO();
    void resetDevice();
    bool getSleepStatus();
    void setSleep();
    void setWake();
    bool getTempDisabled();
    void setTempDisable();
    void setTemEnable();
    uint8_t getClockSource();
    void setClockSource(uint8_t);
    void selfTest(uint8_t, uint8_t, float*);
    void initialize(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);

private:
    int file_handle; // linux file handle for sensor mpu6050

    /* sensitivity
     * modified in @setFullScaleGyroRange(), @setFullScaleAccelRange()
     * used in @getGyroData(), @getAccelData()
     */
    float gyro_sensitivity;
    float accel_sensitivity;
};

#endif

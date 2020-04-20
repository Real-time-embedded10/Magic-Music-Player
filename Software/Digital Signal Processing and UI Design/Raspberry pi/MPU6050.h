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
    MPU6050_SENSOR(uint8_t);//
    uint8_t getSampleRateDivider();//获取采样率分配器
    void setSampleRateDivider(uint8_t);//设置采样率分配器
    unsigned int getSampleRate();//获取采样率
    void setSampleRate(unsigned int);//设定采样率
    uint8_t getDLPFConfig();//获取DLPF配置
    void setDLPFConfig(uint8_t);//
    uint8_t getFullScaleGyroRange();//获得满标度陀螺范围
    void setFullScaleGyroRange(uint8_t);//
    uint8_t getFullScaleAccelRange();//获得满标度加速范围
    void setFullScaleAccelRange(uint8_t);//
    void getAccelRawData(int16_t*, int16_t*, int16_t*);//获取加速原始数据
    void getAccelData(float*, float*, float*);//获取加速数据
    void getGyroRawData(int16_t*, int16_t*, int16_t*);//获取陀螺仪原始数据
    void getGyroData(float*, float*, float*);//获取陀螺仪数据
    void getTempRawData(int16_t*);//获取临时原始数据
    void getTempData(float*);//获取临时数据
    void resetGyroSignalPath();//复位陀螺信号路径
    void resetAccelSignalPath();//复位加速信号路径
    void resetTempSignalPath();//复位温度信号路径
    void resetAllSignalPath();//重置所有信号路径
    bool getFIFOEnabled();//启用FIFO --先进先出
    void setFIFOEnabled();//
    void setFIFODisabled();//
    void resetFIFO();//复位FIFO
    void resetDevice();//复位装置
    bool getSleepStatus();//获取睡眠状态
    void setSleep();//设置睡眠
    void setWake();//设置et
    bool getTempDisabled();//获取温度状态
    void setTempDisable();//设置温度状态
    void setTemEnable();//
    uint8_t getClockSource();//获取时钟源
    void setClockSource(uint8_t);//
    void selfTest(uint8_t, uint8_t, float*);//自测
    void initialize(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);//初始化

private:
    int file_handle; //用于传感器mpu6050的linux文件句柄
    float gyro_sensitivity;
    float accel_sensitivity;
};

#endif

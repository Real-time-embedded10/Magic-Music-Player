#ifndef __MPU6050_Types_H__
#define __MPU6050_Types_H__

#include <stdint.h>
#include "MPU6050_Registers.h"


#define GRAVITY 9.7985
#define MPU6050_DEFAULT_ADDRESS    0x68
#define MPU6050_DEFAULT_WHO_AM_I   0x68

// full scale range
#define MPU6050_GYRO_FS_250DPS     0x00
#define MPU6050_GYRO_FS_500DPS     0x01
#define MPU6050_GYRO_FS_1000DPS    0x02
#define MPU6050_GYRO_FS_2000DPS    0x03
#define MPU6050_ACCEL_FS_2G        0x00
#define MPU6050_ACCEL_FS_4G        0x01
#define MPU6050_ACCEL_FS_8G        0x02
#define MPU6050_ACCEL_FS_16G       0x03

// DLPF
#define MPU6050_DLPF_BW_256        0x00
#define MPU6050_DLPF_BW_188        0x01
#define MPU6050_DLPF_BW_98         0x02
#define MPU6050_DLPF_BW_42         0x03
#define MPU6050_DLPF_BW_20         0x04
#define MPU6050_DLPF_BW_10         0x05
#define MPU6050_DLPF_BW_5          0x06

#endif 
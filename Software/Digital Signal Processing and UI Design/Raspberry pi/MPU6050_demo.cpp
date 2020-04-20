#include <QCoreApplication>
#include <iostream>
#include "MPU6050_Types.h"
#include "MPU6050.h"

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

int main(int argc, char *argv[]){
    MPU6050_SENSOR imu(MPU6050_DEFAULT_ADDRESS);
    // self test
    // self_test_all_range(imu);
    // initialize
    imu.initialize(50, 0x03, 0x00, 0x03, 0x01);
    float xg, yg, zg;
    float xa, ya, za;
    float temp;
    uint32_t sample_count = 0;
    uint32_t sample_time = 0; // ms
    uint32_t last_sample_time = 0; // ms
    while (sample_count < 1000) {
        while (sample_time - last_sample_time < 50) {
            sample_time = millis();
        }
        last_sample_time = sample_time;
        sample_count += 1;
        imu.getGyroData(&xg, &yg, &zg);
        imu.getAccelData(&xa, &ya, &za);
        imu.getTempData(&temp);
        std::cout << "--------------------------------------" << std::endl;
        std::cout << "Time stamp: " << last_sample_time << std::endl;
        std::cout << "Gyroscope output" << std::endl;
        std::cout << "xg: " << xg << " yg: " << yg << " zg: " << zg << std::endl;
        std::cout << "Accelerometer output" << std::endl;
        std::cout << "xa: " << xa << " ya: " << ya << " za: " << za << std::endl;
        std::cout << "Temperature output: " << temp << std::endl;
    }
    std::cout << "--------------------------------------" << std::endl;
    imu.setSleep();
    return 0;
}

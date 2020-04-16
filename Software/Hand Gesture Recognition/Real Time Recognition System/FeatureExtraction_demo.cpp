#include <iostream>
#include "MPU6050_Types.h"
#include "MPU6050.h"
#include "Segmentation.h"
#include "FeatureExtraction.h"

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

int main() {
    MPU6050_SENSOR imu(MPU6050_DEFAULT_ADDRESS);
    SEGMENTATION seg;
    FEATUREEXTRACTION fea;
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
        while (sample_time - last_sample_time < 60) {
            sample_time = millis();
        }
        last_sample_time = sample_time;
        sample_count += 1;
        imu.getGyroData(&xg, &yg, &zg);
        imu.getAccelData(&xa, &ya, &za);
        imu.getTempData(&temp);
        seg.SegmentationProcess(xa, ya, za, xg, yg, zg);
        if (seg.GestureDetectResult == 1) {
            std::cout << "YES" << std::endl;
            fea.extractionProcess(seg.recordTargetXA, seg.recordTargetYA, seg.recordTargetZA, seg.recordTargetXG, seg.recordTargetYG, seg.recordTargetZG);
        }
    }

    imu.setSleep();
    return 0;
}
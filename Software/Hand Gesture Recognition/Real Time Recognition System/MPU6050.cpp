#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "MPU6050.h"
#include "MPU6050_Registers.h"
#include "MPU6050_Types.h"


MPU6050_SENSOR::MPU6050_SENSOR(uint8_t device_address) {
    // Set the GPIO pin to WiringPi mode
    if (wiringPiSetup() < 0) {
        std::cerr << "ERROR: Failed to setup gpio pin numbering scheme to wiringPi mode." << std::endl;
    }
    // Initialize I2C, get the device's file handle
    file_handle = wiringPiI2CSetup(device_address);
    if (file_handle < 0) {
        std::cerr << "ERROR: Failed to setup I2C with device address: " << device_address << std::endl;
    }
    // Check if the device is MPU6050
    uint8_t device_id = wiringPiI2CReadReg8(file_handle, MPU6050_RA_WHO_AM_I);
    if (device_id != MPU6050_DEFAULT_WHO_AM_I) {
        std::cerr << "ERROR: Wrong device, this is not a mpu6050 sensor." << std::endl;
        std::cerr << std::hex << (int)device_id << std::endl;
    }
}

/* sample rate config 
 * Determined by register MPU6050_RA_SMPLRT_DIV
 * Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV)
 * If the low-pass filter is not enabled, that is, the low-pass filter is set to 0 or 7, the gyro output frequency is 8kHz;
 * If low-pass filter is enabled, the gyro output frequency is 1kHz.
  */

uint8_t MPU6050_SENSOR::getSampleRateDivider() {
    return wiringPiI2CReadReg8(file_handle, MPU6050_RA_SMPLRT_DIV);
}

void MPU6050_SENSOR::setSampleRateDivider(uint8_t divider) {
    wiringPiI2CWriteReg8(file_handle, MPU6050_RA_SMPLRT_DIV, divider);
}

/* Since the sampling rate is related to SMPLRT_DIV and DLPF_CFG, these function can directly set the sampling rate */

unsigned int MPU6050_SENSOR::getSampleRate() {
    uint8_t dlpf_config = getDLPFConfig();
    unsigned int gyro_output_rate = (dlpf_config == 0 || dlpf_config == 7) ? 8000 : 1000;
    uint8_t divider = getSampleRateDivider();
    return gyro_output_rate / (1 + divider);
}

void MPU6050_SENSOR::setSampleRate(unsigned int rate) {
    uint8_t dlpf_config = getDLPFConfig();
    unsigned int gyro_output_rate = (dlpf_config == 0 || dlpf_config == 7) ? 8000 : 1000;
    uint8_t divider = gyro_output_rate / rate - 1;
    setSampleRateDivider(divider);
}

/* DLPF config 
 * The low-pass filter is determined by the lower three bits of the register MPU6050_RA_CONFIG.
 *  It is recommended to set the value to half of the sampling frequency of the Gyroscope. For example, the sampling frequency is 125Hz, and the DLPF is 42Hz.
 *          |   ACCELEROMETER    |           GYROSCOPE
 * DLPF_CFG | Bandwidth | Delay  | Bandwidth | Delay  | Sample Rate
 * ---------+-----------+--------+-----------+--------+-------------
 * 0        | 260Hz     | 0ms    | 256Hz     | 0.98ms | 8kHz
 * 1        | 184Hz     | 2.0ms  | 188Hz     | 1.9ms  | 1kHz
 * 2        | 94Hz      | 3.0ms  | 98Hz      | 2.8ms  | 1kHz
 * 3        | 44Hz      | 4.9ms  | 42Hz      | 4.8ms  | 1kHz
 * 4        | 21Hz      | 8.5ms  | 20Hz      | 8.3ms  | 1kHz
 * 5        | 10Hz      | 13.8ms | 10Hz      | 13.4ms | 1kHz
 * 6        | 5Hz       | 19.0ms | 5Hz       | 18.6ms | 1kHz
 * 7        |   -- Reserved --   |   -- Reserved --   | Reserved
 */

uint8_t MPU6050_SENSOR::getDLPFConfig() {
    return wiringPiI2CReadReg8(file_handle, MPU6050_RA_CONFIG) & 0x07;
}

void MPU6050_SENSOR::setDLPFConfig(uint8_t config) {
    // Only change the value of the lower three digits
    uint8_t whole_byte = wiringPiI2CReadReg8(file_handle, MPU6050_RA_CONFIG) & 0xF8 | config;
    wiringPiI2CWriteReg8(file_handle, MPU6050_RA_CONFIG, whole_byte);
}

/* Full scale gyroscope range
 * Determined by the third and fourth bits of register MPU6050_RA_GYRO_CONFIG
 * 0 = +/- 250 degrees/sec
 * 1 = +/- 500 degrees/sec
 * 2 = +/- 1000 degrees/sec
 * 3 = +/- 2000 degrees/sec
 */

uint8_t MPU6050_SENSOR::getFullScaleGyroRange() {
    return wiringPiI2CReadReg8(file_handle, MPU6050_RA_GYRO_CONFIG) & 0x18 >> 3;
}

void MPU6050_SENSOR::setFullScaleGyroRange(uint8_t range) {
    // Only change the third and fourth digits
    uint8_t whole_byte = wiringPiI2CReadReg8(file_handle, MPU6050_RA_GYRO_CONFIG) & 0x07 | (range << 3);
    wiringPiI2CWriteReg8(file_handle, MPU6050_RA_GYRO_CONFIG, whole_byte);

    /* Modified the sensitivity of gyroscope
     * This value is related to the change of the measuring range, and will only be used in @getGyroData,
     * Modifying it here can avoid other repeated calling steps.
     * FS_SEL | Full Scale Range   | LSB Sensitivity
     * -------+--------------------+----------------
     * 0      | +/- 250 degrees/s  | 131 LSB/deg/s
     * 1      | +/- 500 degrees/s  | 65.5 LSB/deg/s
     * 2      | +/- 1000 degrees/s | 32.8 LSB/deg/s
     * 3      | +/- 2000 degrees/s | 16.4 LSB/deg/s
     */
    switch (range) {
    case MPU6050_GYRO_FS_250DPS:
        gyro_sensitivity = 131.0;
        break;
    case MPU6050_GYRO_FS_500DPS:
        gyro_sensitivity = 65.5;
        break;
    case MPU6050_GYRO_FS_1000DPS:
        gyro_sensitivity = 32.8;
        break;
    case MPU6050_GYRO_FS_2000DPS:
        gyro_sensitivity = 16.4;
        break;
    }
}

/* full scale accelerometer range
 * Determined by the third and fourth bits of register MPU6050_RA_ACCEL_CONFIG
 * 0 = +/- 2g
 * 1 = +/- 4g
 * 2 = +/- 8g
 * 3 = +/- 16g
 */

uint8_t MPU6050_SENSOR::getFullScaleAccelRange() {
    return wiringPiI2CReadReg8(file_handle, MPU6050_RA_ACCEL_CONFIG) & 0x18 >> 3;
}

void MPU6050_SENSOR::setFullScaleAccelRange(uint8_t range) {
    // Only change the third and fourth digits
    uint8_t whole_byte = wiringPiI2CReadReg8(file_handle, MPU6050_RA_ACCEL_CONFIG) & 0x07 | (range << 3);
    wiringPiI2CWriteReg8(file_handle, MPU6050_RA_ACCEL_CONFIG, whole_byte);

    /* Modified the sensitivity of accelerometer
     * This value is related to the change of the measuring range, and will only be used in @getAccelData.
     * Modifying it here can avoid other repeated calling steps.
     * AFS_SEL | Full Scale Range | LSB Sensitivity
     * --------+------------------+----------------
     * 0       | +/- 2g           | 16384 LSB/g
     * 1       | +/- 4g           | 8192 LSB/g
     * 2       | +/- 8g           | 4096 LSB/g
     * 3       | +/- 16g          | 2048 LSB/g
     */
    switch (range) {
    case MPU6050_ACCEL_FS_2G:
        accel_sensitivity = 16384.0;
        break;
    case MPU6050_ACCEL_FS_4G:
        accel_sensitivity = 8192.0;
        break;
    case MPU6050_ACCEL_FS_8G:
        accel_sensitivity = 4096.0;
        break;
    case MPU6050_ACCEL_FS_16G:
        accel_sensitivity = 2048.0;
        break;
    }
}

/* Accelerometer output
 * The output is a 16-bit signed integer of three axes, and divide them by Sensitivity to obtain the rate of acceleration of gravity.
 * In order to obtain the acceleration reading in m/s^2, the GRAVITY constant is set in the "MPU6050_Types.h" file
 */

void MPU6050_SENSOR::getAccelRawData(int16_t* xa, int16_t* ya, int16_t* za) {
    *xa = wiringPiI2CReadReg8(file_handle, MPU6050_RA_ACCEL_XOUT_H);
    *xa <<= 8;
    *xa |= wiringPiI2CReadReg8(file_handle, MPU6050_RA_ACCEL_XOUT_L);
    *ya = wiringPiI2CReadReg8(file_handle, MPU6050_RA_ACCEL_YOUT_H);
    *ya <<= 8;
    *ya |= wiringPiI2CReadReg8(file_handle, MPU6050_RA_ACCEL_YOUT_L);
    *za = wiringPiI2CReadReg8(file_handle, MPU6050_RA_ACCEL_ZOUT_H);
    *za <<= 8;
    *za |= wiringPiI2CReadReg8(file_handle, MPU6050_RA_ACCEL_ZOUT_L);
}

void MPU6050_SENSOR::getAccelData(float* xa, float* ya, float* za) {
    int16_t xa_raw, ya_raw, za_raw;
    getAccelRawData(&xa_raw, &ya_raw, &za_raw);
    *xa = (float)xa_raw / accel_sensitivity * GRAVITY;
    *ya = (float)ya_raw / accel_sensitivity * GRAVITY;
    *za = (float)za_raw / accel_sensitivity * GRAVITY;
}

/* Gyroscope output
 * The output is a 16-bit signed integer of three axes, and divide them by Sensitivity to obtain the angular velocity in degrees/second.
 */

void MPU6050_SENSOR::getGyroRawData(int16_t* xg, int16_t* yg, int16_t* zg) {
    *xg = wiringPiI2CReadReg8(file_handle, MPU6050_RA_GYRO_XOUT_H);
    *xg <<= 8;
    *xg |= wiringPiI2CReadReg8(file_handle, MPU6050_RA_GYRO_XOUT_L);
    *yg = wiringPiI2CReadReg8(file_handle, MPU6050_RA_GYRO_YOUT_H);
    *yg <<= 8;
    *yg |= wiringPiI2CReadReg8(file_handle, MPU6050_RA_GYRO_YOUT_L);
    *zg = wiringPiI2CReadReg8(file_handle, MPU6050_RA_GYRO_ZOUT_H);
    *zg <<= 8;
    *zg |= wiringPiI2CReadReg8(file_handle, MPU6050_RA_GYRO_ZOUT_L);
}

void MPU6050_SENSOR::getGyroData(float* xg, float* yg, float* zg) {
    int16_t xg_raw, yg_raw, zg_raw;
    getGyroRawData(&xg_raw, &yg_raw, &zg_raw);
    *xg = (float)xg_raw / gyro_sensitivity;
    *yg = (float)yg_raw / gyro_sensitivity;
    *zg = (float)zg_raw / gyro_sensitivity;
}


/* Temperature output
 * The output is a 16-bit signed integer and needs to be converted in degrees Celsius.
 */

void MPU6050_SENSOR::getTempRawData(int16_t* temp) {
    *temp = wiringPiI2CReadReg8(file_handle, MPU6050_RA_TEMP_OUT_H);
    *temp <<= 8;
    *temp |= wiringPiI2CReadReg8(file_handle, MPU6050_RA_TEMP_OUT_L);
}

void MPU6050_SENSOR::getTempData(float* temp) {
    int16_t raw;
    getTempRawData(&raw);
    *temp = (float)raw / 340.0 + 36.53;
}

/* Reset temperature signal path
 * Determined by the zeroth bit of register MPU6050_RA_SIGNAL_PATH_RESET
 */

void MPU6050_SENSOR::resetTempSignalPath() {
    uint8_t whole_byte = wiringPiI2CReadReg8(file_handle, MPU6050_RA_SIGNAL_PATH_RESET) | 0x01;
    wiringPiI2CWriteReg8(file_handle, MPU6050_RA_SIGNAL_PATH_RESET, whole_byte);
}

/* Reset accelerometer signal path
 * Determined by the first bit of register MPU6050_RA_SIGNAL_PATH_RESET
 */

void MPU6050_SENSOR::resetAccelSignalPath() {
    uint8_t whole_byte = wiringPiI2CReadReg8(file_handle, MPU6050_RA_SIGNAL_PATH_RESET) | 0x02;
    wiringPiI2CWriteReg8(file_handle, MPU6050_RA_SIGNAL_PATH_RESET, whole_byte);
}

/* Reset gyroscope signal path
 * Determined by the second bit of register MPU6050_RA_SIGNAL_PATH_RESET
 */

void MPU6050_SENSOR::resetGyroSignalPath() {
    uint8_t whole_byte = wiringPiI2CReadReg8(file_handle, MPU6050_RA_SIGNAL_PATH_RESET) | 0x04;
    wiringPiI2CWriteReg8(file_handle, MPU6050_RA_SIGNAL_PATH_RESET, whole_byte);
}

/* Reset all signal path
 * Determined by the zeroth bit of register MPU6050_RA_USER_CTRL
 */

void MPU6050_SENSOR::resetAllSignalPath() {
    uint8_t whole_byte = wiringPiI2CReadReg8(file_handle, MPU6050_RA_USER_CTRL) | 0x01;
    wiringPiI2CWriteReg8(file_handle, MPU6050_RA_USER_CTRL, whole_byte);
}

/* FIFO buffer switch
 * Determined by register MPU6050_RA_FIFO_EN
 *   index   |  7   | 6  | 5  | 4  |   3   |  2   |  1   |  0
 * ----------+------+----+----+----+-------+------+------+-------
 *  describe | TEMP | XG | YG | ZG | ACCEL | SLV2 | SLV1 | SLV0
 * The fifth bit of the register MPU6050_RA_I2C_MST_CTRL is the FIFO_ENABLE of SLV3
 * Since multiple I2C devices are currently not used (only one device is used in this project), MST (master) and SLV (slave) related settings are not implemented
 */

 /* FIFO config and reset
  * The sixth bit of register MPU6050_RA_USER_CTRL is used to enable FIFO, and the second bit is used to reset FIFO.
  */

bool MPU6050_SENSOR::getFIFOEnabled() {
    return (wiringPiI2CReadReg8(file_handle, MPU6050_RA_USER_CTRL) & 0x40) == 0x40;
}

void MPU6050_SENSOR::setFIFOEnabled() {
    uint8_t whole_byte = wiringPiI2CReadReg8(file_handle, MPU6050_RA_USER_CTRL) | 0x40;
    wiringPiI2CWriteReg8(file_handle, MPU6050_RA_USER_CTRL, whole_byte);
}

void MPU6050_SENSOR::setFIFODisabled() {
    uint8_t whole_byte = wiringPiI2CReadReg8(file_handle, MPU6050_RA_USER_CTRL) & 0xBF;
    wiringPiI2CWriteReg8(file_handle, MPU6050_RA_USER_CTRL, whole_byte);
}

void MPU6050_SENSOR::resetFIFO() {
    uint8_t whole_byte = wiringPiI2CReadReg8(file_handle, MPU6050_RA_USER_CTRL) | 0x04;
    wiringPiI2CWriteReg8(file_handle, MPU6050_RA_USER_CTRL, whole_byte);
}

/* Reset device
 * Determined by the seventh bit of the first power management register MPU6050_RA_PWR_MGMT_1
 */

void MPU6050_SENSOR::resetDevice() {
    uint8_t whole_byte = wiringPiI2CReadReg8(file_handle, MPU6050_RA_PWR_MGMT_1) | 0x80;
    wiringPiI2CWriteReg8(file_handle, MPU6050_RA_PWR_MGMT_1, whole_byte);
}

/* Sleep
 * Determined by the sixth bit of the first power management register MPU6050_RA_PWR_MGMT_1
 */

bool MPU6050_SENSOR::getSleepStatus() {
    return (wiringPiI2CReadReg8(file_handle, MPU6050_RA_PWR_MGMT_1) & 0x40) == 0x40;
}

void MPU6050_SENSOR::setSleep() {
    uint8_t whole_byte = wiringPiI2CReadReg8(file_handle, MPU6050_RA_PWR_MGMT_1) | 0x40;
    wiringPiI2CWriteReg8(file_handle, MPU6050_RA_PWR_MGMT_1, whole_byte);
}

void MPU6050_SENSOR::setWake() {
    uint8_t whole_byte = wiringPiI2CReadReg8(file_handle, MPU6050_RA_PWR_MGMT_1) & 0xBF;
    wiringPiI2CWriteReg8(file_handle, MPU6050_RA_PWR_MGMT_1, whole_byte);
}

/* Temperature sensor disable
 * Determined by the third bit of the first power management register MPU6050_RA_PWR_MGMT_1
 */

bool MPU6050_SENSOR::getTempDisabled() {
    return (wiringPiI2CReadReg8(file_handle, MPU6050_RA_PWR_MGMT_1) & 0x08) == 0x08;
}

void MPU6050_SENSOR::setTempDisable() {
    uint8_t whole_byte = wiringPiI2CReadReg8(file_handle, MPU6050_RA_PWR_MGMT_1) | 0x08;
    wiringPiI2CWriteReg8(file_handle, MPU6050_RA_PWR_MGMT_1, whole_byte);
}

void MPU6050_SENSOR::setTemEnable() {
    uint8_t whole_byte = wiringPiI2CReadReg8(file_handle, MPU6050_RA_PWR_MGMT_1) & 0xF7;
    wiringPiI2CWriteReg8(file_handle, MPU6050_RA_PWR_MGMT_1, whole_byte);
}

/* Clock source settings
 * Determined by the 1-3 bit of the first power management register MPU6050_RA_PWR_MGMT_1
 * The recommended setting is 1, which uses the gyroscope's X axis.
 * CLK_SEL | Clock Source
 * --------+--------------------------------------
 * 0       | Internal oscillator
 * 1       | PLL with X Gyro reference
 * 2       | PLL with Y Gyro reference
 * 3       | PLL with Z Gyro reference
 * 4       | PLL with external 32.768kHz reference
 * 5       | PLL with external 19.2MHz reference
 * 6       | Reserved
 * 7       | Stops the clock and keeps the timing generator in reset
 */

uint8_t MPU6050_SENSOR::getClockSource() {
    return wiringPiI2CReadReg8(file_handle, MPU6050_RA_PWR_MGMT_1) & 0x07;
}

void MPU6050_SENSOR::setClockSource(uint8_t source) {
    uint8_t whole_byte = wiringPiI2CReadReg8(file_handle, MPU6050_RA_PWR_MGMT_1) & 0xF8 | source;
    wiringPiI2CWriteReg8(file_handle, MPU6050_RA_PWR_MGMT_1, whole_byte);
}

/* self test */

void MPU6050_SENSOR::selfTest(uint8_t gyro_range, uint8_t accel_range, float* differences) {
    uint8_t raw[4];
    uint8_t self_test_response[6];

    // Set the range of gyroscope and accelerometer, and start self-test
    setFullScaleGyroRange(gyro_range);
    setFullScaleAccelRange(accel_range);
    wiringPiI2CWriteReg8(file_handle, MPU6050_RA_GYRO_CONFIG, 0xE0 | (gyro_range << 3));
    wiringPiI2CWriteReg8(file_handle, MPU6050_RA_ACCEL_CONFIG, 0xE0 | (accel_range << 3));
    delay(1000);

    // Read the result
    raw[0] = wiringPiI2CReadReg8(file_handle, MPU6050_RA_SELF_TEST_X);
    raw[1] = wiringPiI2CReadReg8(file_handle, MPU6050_RA_SELF_TEST_Y);
    raw[2] = wiringPiI2CReadReg8(file_handle, MPU6050_RA_SELF_TEST_Z);
    raw[3] = wiringPiI2CReadReg8(file_handle, MPU6050_RA_SELF_TEST_A);
    // xg
    self_test_response[0] = raw[0] & 0x1F;
    // yg
    self_test_response[1] = raw[1] & 0x1F;
    // zg
    self_test_response[2] = raw[2] & 0x1F;
    // xa
    self_test_response[3] = ((raw[0] & 0xE0) >> 3) | ((raw[4] & 0x30) >> 4);
    // ya
    self_test_response[4] = ((raw[1] & 0xE0) >> 3) | ((raw[4] & 0x0C) >> 2);
    // za
    self_test_response[5] = ((raw[2] & 0xE0) >> 3) | (raw[4] & 0x03);

    // Calculate factory trim
    float factory_trim[6];
    factory_trim[0] = 25.0 * gyro_sensitivity * pow(1.046, ((float)self_test_response[0] - 1.0));
    factory_trim[1] = -25.0 * gyro_sensitivity * pow(1.046, ((float)self_test_response[1] - 1.0));
    factory_trim[2] = 25.0 * gyro_sensitivity * pow(1.046, ((float)self_test_response[2] - 1.0));
    factory_trim[3] = 0.34 * accel_sensitivity * pow((0.92 / 0.34), (((float)self_test_response[3] - 1.0) / 30.0));
    factory_trim[4] = 0.34 * accel_sensitivity * pow((0.92 / 0.34), (((float)self_test_response[4] - 1.0) / 30.0));
    factory_trim[5] = 0.34 * accel_sensitivity * pow((0.92 / 0.34), (((float)self_test_response[5] - 1.0) / 30.0));

    // Calculate the percentage
    for (int i = 0; i < 6; ++i) {
        differences[i] = ((float)self_test_response[i] - factory_trim[i]) / factory_trim[i] * 100.0 + 100.0;
    }
}

// Initialization
void MPU6050_SENSOR::initialize(uint8_t sample_rate, uint8_t dlpf_config, uint8_t gyro_range, uint8_t accel_range, uint8_t clock_source) {
    // Reset device
    resetDevice();
    delay(500);
    setWake();
    delay(100);
    // Set low pass filter
    setDLPFConfig(dlpf_config);
    // Set sampling rate
    setSampleRate(sample_rate);
    // Set gyroscope, acceleration measurement range
    setFullScaleGyroRange(gyro_range);
    setFullScaleAccelRange(accel_range);
    // Set clock sourece
    setClockSource(clock_source);
    // Disable FIFO
    setFIFODisabled();
}
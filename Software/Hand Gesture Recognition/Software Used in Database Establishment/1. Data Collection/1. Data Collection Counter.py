import smbus
import time
import numpy as np

# Define register addresses
MPU_ACCEL_XOUT1 = 0x3b
MPU_ACCEL_XOUT2 = 0x3c
MPU_ACCEL_YOUT1 = 0x3d
MPU_ACCEL_YOUT2 = 0x3e
MPU_ACCEL_ZOUT1 = 0x3f
MPU_ACCEL_ZOUT2 = 0x40
MPU_GYRO_XOUT1 = 0x43
MPU_GYRO_XOUT2 = 0x44
MPU_GYRO_YOUT1 = 0x45
MPU_GYRO_YOUT2 = 0x46
MPU_GYRO_ZOUT1 = 0x47
MPU_GYRO_ZOUT2 = 0x48
MPU_POWER1 = 0x6b
MPU_POWER2 = 0x6c
address = 0x68

# Read information
def read_word_2c(adr):
    val = (bus.read_byte_data(address, adr) << 8) + bus.read_byte_data(address, adr + 1)
    if (val >= 0x8000):
        return -((65535 - val) + 1)
    else:
        return val

bus = smbus.SMBus(1) # 1 means '/dev/i2c-1'
bus.write_byte_data(address, MPU_POWER1, 0)

# Initialize the matrix that will be used for the counter
test_old = np.zeros((23, 1), dtype='int16')
test_new = np.zeros((23, 1), dtype='int16')
number = 0

while (1):
    # Read information from sensor
    AX = read_word_2c(MPU_ACCEL_XOUT1)
    AY = read_word_2c(MPU_ACCEL_YOUT1)
    AZ = read_word_2c(MPU_ACCEL_ZOUT1)
    GX = read_word_2c(MPU_GYRO_XOUT1)
    GY = read_word_2c(MPU_GYRO_YOUT1)
    GZ = read_word_2c(MPU_GYRO_ZOUT1)
    
    # Pre-process information read from sensor for better detection result.
    AX = AX * 150
    AY = AY * 300
    AZ = AZ * 100
    GX = GX * 10
    GY = GY * 10
    GZ = GZ * 10
    
    # Detect large change of data
    test = 0
    if ((AX > 700) or (AX < -700)):
        test = 1
    else:
        if ((AY > 700) or (AY < -700)):
            test = 1
        else:
            if ((AZ > 1700) or (AZ < 200)):
                test = 1
            else:
                if ((GX > 700) or (GX < -700)):
                    test = 1
                else:
                    if ((GY > 700) or (GY < -700)):
                        test = 1
                    else:
                        if ((GZ > 700) or (GZ < -700)):
                            test = 1
                        else:
                            test = 0
    
    test_new[22] = test
    for r in range(22):
        test_new[r] = test_old[r+1]  # the r itme of position_judge is equal to the (r-1) itme of postion.
    test_old = test_new
   
    # Counter
    if (sum(test_new[0:20]) == 0) & (test_new[20] == 1) & (sum(test_new[21:23]) != 0):
        number = number+1
        print(number)
           

    AX2 = str(AX)
    AY2 = str(AY)
    AZ2 = str(AZ)
    GX2 = str(GX)
    GY2 = str(GY)
    GZ2 = str(GZ)
    
    # Save information in './result.txt'
    with open('./result.txt', 'a') as file_handle:
        file_handle.write(AX2)
        file_handle.write('  ')
        file_handle.write(AY2)
        file_handle.write('  ')
        file_handle.write(AZ2)
        file_handle.write('  ')
        file_handle.write(GX2)
        file_handle.write('  ')
        file_handle.write(GY2)
        file_handle.write('  ')
        file_handle.write(GZ2)
        file_handle.write('\n')
    time.sleep(0.05)

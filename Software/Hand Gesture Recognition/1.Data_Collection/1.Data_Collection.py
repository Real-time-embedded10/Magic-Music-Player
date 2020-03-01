import smbus
import time

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

def read_word_2c(adr):
    val = (bus.read_byte_data(address,adr) << 8) + bus.read_byte_data(address,adr+1)
    if (val >= 0x8000):
        return -((65535 - val)+1)
    else:
        return val

bus = smbus.SMBus(1)    
bus.write_byte_data(address, MPU_POWER1, 0)

while (1):
    AX = read_word_2c(MPU_ACCEL_XOUT1) /100
    AY = read_word_2c(MPU_ACCEL_YOUT1)  / 100
    AZ = read_word_2c(MPU_ACCEL_ZOUT1) / 100
    
    GX = read_word_2c(MPU_GYRO_XOUT1) / 100
    GY = read_word_2c(MPU_GYRO_YOUT1) / 100
    GZ = read_word_2c(MPU_GYRO_ZOUT1) / 100
    
    #print('AX =', AX, 'AY = ', AY,'AZ = ',AZ)
    #print('GX =', GX, 'GY = ', GY,'GZ = ',GZ)
    
    AX2 = str(AX)
    AY2 = str(AY)
    AZ2 = str(AZ)
    GX2 = str(GX)
    GY2 = str(GY)
    GZ2 = str(GZ)
    with open('./result.txt','a') as file_handle:
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
    time.sleep(0.005)

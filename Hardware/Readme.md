Hardware Design
==
MPU-60X0 is the world's first 9-axis motion processor. It integrates a 3-axis MEMS gyroscope to measure angle, a 3-axis MEMS accelerometer to measure acceleration, and a scalable digital motion processor (DMP), which can be connected to a third-party digital sensor using I2C interface , such as a magnetometer. After expansion, it can output a 9-axis signal through its I2C interface. MPU-60X0 can also connect non-inertial digital sensors, such as pressure sensors, through its I2C interface. DMP receives and processes data from gyroscopes, accelerometers, and external sensors. The processing results can be read from DMP registers, or buffered by FIFO, and output posture-resolved data to the application side through the main I2C interface.<br>

The MPU-60X0 uses three 16-bit ADCs for the gyroscope and accelerometer, respectively, and converts the analog value it measures into a digital output. In order to accurately track fast and slow movements, the measurement range of the sensor is user-controllable, the gyro measurement range is ± 250, ± 500, ± 1000, ± 2000 ° / sec (dps), and the accelerometer measurement range is ± 2, ± 4, ± 8, ± 16g (gravity acceleration). A 1024-byte FIFO helps reduce system power consumption. Communication with all device registers uses 400kHz I2C interface or 1MHz SPI interface (SPI is only available for MPU-6000). For applications that require high-speed transmission, 20MHz SPI is available for reading and interrupting registers. In addition, a temperature sensor and an oscillator with only ± 1% variation in the working environment are embedded on the chip. The chip size is 4 × 4 × 0.9mm, and it adopts QFN package (leadless square package), which can withstand a maximum of 10000g shock, and has a programmable low-pass filter. Regarding power supply, MPU-60X0 can support VDD range 2.5V ± 5%, 3.0V ± 5%, or 3.3V ± 5%. In addition, MPU-6050 also has a VLOGIC pin, which is used to provide logic levels for I2C output. The VLOGIC voltage can be 1.8 ± 5% or VDD.<br>

**Features of MPU6050 include:**<br>
①	Digitally output 6-axis or 9-axis (requires external magnetic sensor) rotation matrix, quaternion, Euler Angle forma fusion calculation data (requires DMP support).<br>
②	3-axis angular velocity sensor (gyroscope) with 131 LSBs / ° / sec sensitivity and full-scale sensing range of ± 250, ± 500, ± 1000 and ± 2000 ° / sec.<br>
③	Integrated 3-axis acceleration sensor with programmable control range of ± 2g, ± 4g, ± 8g and ± 16g.<br>
④	Remove the sensitivity between the accelerator and the gyroscope axis, reduce the influence of the setting and the drift of the sensor.<br>
⑤	Built-in DMP engine can reduce the load of complex fusion calculation data of MCU, sensor synchronization, posture sensing, etc.<br>
⑥	Built-in operation time deviation and magnetic sensor calibration calculation technology, eliminating the need for customers to perform additional calibration.<br>
⑦	Coming with a digital temperature sensor.<br>
⑧	With digital input synchronization pin (Sync pin) supports video electronic shadow stabilization technology and GPS.<br>
⑨	Programmable interruption, support gesture recognition, panning, zooming in and out of the screen, scrolling, rapid descent interruption, high-G interruption, zero motion sensing, touch sensing, shaking sensing function.<br>
⑩	VDD power supply voltage is 2.5V ± 5%, 3.0V ± 5%, 3.3V ± 5%; VLOGIC can be as low as 1.8V ± 5%.<br>
⑪	Gyroscope working current: 5mA, gyroscope standby current: 5uA; accelerator working current: 500uA, accelerator power saving mode current: 40uA @ 10Hz.<br>
⑫	Comes with 1024-byte FIFO, which helps reduce system power consumption.<br>
⑬	I2C communication interface up to 400Khz.<br>
⑭	Ultra-small package size: 4x4x0.9mm (QFN).<br>

**Circuit Design**<br>
The Block Diagram of MPU6050:<br>
![](https://github.com/Real-time-embedded10/Magic-Music-Player/blob/master/Hardware/MPU6050-Block%20Diagram.png)<br>
The above picture is the internal structure diagram of MPU6050. Among them, SCL and SDA are I2C interfaces connected to MCU. Raspberry Pi controls MPU6050 through this I2C interface. There is also an I2C interface: AUX_CL and AUX_DA. This interface can be used to connect external slave devices. For example, magnetic sensors, so that a nine-axis sensor can be formed. VLOGIC is the voltage of the IO port. This pin can be as low as 1.8V. We generally connect it directly to VDD. AD0 is the address control pin from the I2C interface (connected to MCU). This pin controls the lowest bit of the IIC address. If it is connected to GND, the I2C address of MPU6050 is: 0X68, if it is connected to VDD, it is 0X69. Note: The address here does not contain the lowest bit of data transmission (the lowest bit is used to indicate read and write).<br>

The Schematic Circuit Diagram:<br>
![](https://github.com/Real-time-embedded10/Magic-Music-Player/blob/master/Hardware/Schematic%20Circuit%20Diagram.png)<br>
Because the voltage working range of MPU60X0 is 2.375V-3.46V, a 3.3V low dropout voltage regulator circuit is added to the circuit diagram design to power the MPU6050, so the MPU6050 chip can be connected to the 3.3V or 5V output power of the Raspberry Pi. Pull-up resistors of 4.7K are added at both SDA and SCL, and external pull-up resistors can be eliminated. In addition, there is also a 4.7K pull-down resistor at AD0. In the actual connection, AD0 is floating, and the default I2C address is 0X68.<br>

For detailed information or data related to MPU6050, please refer to [the uploaded datasheet](https://github.com/Real-time-embedded10/Magic-Music-Player/blob/master/Hardware/MPU-60X0-Datasheet.pdf).<br>

Introduction
==
The core component in the hardware design is the MPU6050 chip, which can stably obtain the accelerometer output, gyroscope output, and temperature. The MPU6050 in the project is used to determine the direction of the hand gestures. At the same time, an LDO circuit is used in our circuit design to provide a stable 3.3V power supply for the MPU6050 to avoid burning the core chip with too high a voltage. The main component of the LDO circuit is LM7803, which can stably output 5V input voltage as 3.3V output voltage.<br>

For more information about component and circuit design, please refer to our [wiki](https://github.com/Real-time-embedded10/Magic-Music-Player/wiki/Hardware-Design).

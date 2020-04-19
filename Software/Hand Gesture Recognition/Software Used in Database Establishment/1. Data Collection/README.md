Data Collection
==
When training the model, large enough samples are required. Samples of 6 hand gestures (forward, backward, left, right, up and down) were recorded, and each word was played by 6 people with different ages and sexes, collecting a total of 180 samples of each gesture.<br>
Since it is more convenient to collect data by python than C++ (every time changing the stored file name, you don't need to re-run `make` and then `./main`), this file was written by python.<br>
[Here](https://github.com/Real-time-embedded10/Magic-Music-Player/tree/master/Software/Hand%20Gesture%20Recognition/DATABASE/Original%20Data) is the original DATABASE collected. <br>

Hardware Selection
--
In this project, the hand movement are needed to be analyzed, and thereby accelerometer and gyroscope sensors are selected as tools to obtain information of gestures. MPU9250 and MPU6050 are two commonly used sensors to be considered, and both have functions of accelerometer and gyroscope. They are almost the same, but MPU9250 has a magnetometer, meaning that it has a reference frame with a fixed coordinate system. However, this function is not necessary, so we finally chose MPU6050 which is relatively cheaper.<br>

Parameters Setting
--
**Sampling speed** and **acceleration range** are the two main significant parameters. During data collection, the actual sampling period is set to 0.05s (20Hz), so the sampling speed of the sensor needs to be greater than 20Hz. The acceleration range is set from -8g to 8g, since according to our test, the real-time acceleration range will never exceed 8g.<br>
There are two **communication methods** to read data from MPU6050 to Raspberry Pi, namely Universal Asynchronous Receiver/Transmitter (UART) and Inter-Integrated Circuit (I2C). I2C was selected. It has a half-duplex mode, which means that several devices can share the same I2C line at the same time. Another reason for using I2C communication method is that the output data can be obtained from the corresponding address in a more accurate and stable way.<br>

Install I2C library.<br>
```
sudo apt-get install i2c-tools
```

Detect whether I2C device is successfully connected and find the corresponding address.
```
sudo i2cdetect -y 1
```

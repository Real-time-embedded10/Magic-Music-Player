Magic-Music-Player
==
This project aims to design a real-time gesture-based Magic Music System, capable of adding sound effects (including tone and/or volume) in real time using defined hand gestures.<br>

![](https://github.com/Real-time-embedded10/Magic-Music-Player/blob/master/Image/Gesture%20Based%20Music%20Player.jpg) 

Introduction
--
**Main Function**<br>
Export source from PC; <br>
Equipped control UI on PC; <br>
Recognize Hand Gesture in real time; <br>
Change music tone/volume by gestures in the process of playing music.<br>

**Hardware Requirement**<br>
Accelerometer and Gyroscope: Sensors of Hand Gesture <br>
Raspberry Pi: Real-time Hand Gesture Recognition <br>
PC: Graphical User Interface and UI Music Player <br>

**Software Requirement**<br>
I2C system to obtain data from sensors. <br>
Pre-processing method to extract useful information of hand gestures. <br>
Marchine learning model to classify hand gestures.<br>
Communication system to realize wireless connection bewteen PC and raspberry pi.<br>
Digital signal processing algorithm to process song based on control signal received from raspberry pi.<br>

Further information is available at our [wiki](https://github.com/Real-time-embedded10/Magic-Music-Player/wiki).<br>

Pre-Requirement
--
Install libraries in Raspberry pi.
```
sudo apt-get install i2c-tools
sudo apt-get install wiringpi
```
and make sure that all relevant files are in one folder.<br>

To Run
--
```
cmake .
make
./main
```

Authors
--
**tashanguanyan** - Xinyun Jiang (2227272J): I2C system, Hand Gesture Recognition (Database Establishment, Machine Learning Model Training and Real-time Recoginition System).<br>
**YangDING0201** - Yang Ding (2492952D): UI MusicPlayer for PC & Rasberry Pi (Communication and Digital Signal Processing).<br>
**LianfengWu** - Lianfeng Wu (2227370W): Hardware (PCB Design). <br>
<br>
Please follow us [Twitter](https://twitter.com/MusicTeam10).<br>




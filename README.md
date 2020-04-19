Magic-Music-Player
==
This project aims to design a real-time gesture-based Magic Music System, capable of adding sound effects (including tone and/or volume) in real time using defined hand gestures.<br>

![](https://github.com/Real-time-embedded10/Magic-Music-Player/blob/master/Image/Gesture%20Based%20Music%20Player.jpg) 

Introduction
--
**Main Function**<br>
Export source from PC; <br>
Equipped control UI on PC; <br>
Recognise Hand Gesture in real time; <br>
Change music tone/volume by gestures in the process of playing music.<br>

**Hardware Requirement**<br>
Accelerometer and Gyroscope: Sensors of Hand Gesture <br>
Raspberry Pi: Real-time Hand Gesture Recognition <br>
PC: Graphical User Interface<br>

**Software Requirement**<br>
I2C system to obtain data from sensors. <br>
Pre-processing method to extract useful information of hand gestures. <br>
Marchine learning model to classify hand gestures.<br>
Communication system to realize wireless connection bewteen PC and raspberry pi.<br>
Digital signal processing algorithm to process song based on control signal received from raspberry pi.<br>

Our Work
--
[***PCB Design***](https://github.com/Real-time-embedded10/Magic-Music-Player/tree/master/Hardware)<br>
A current circuit was designed, and it can obtain information about accelerometer output, gyroscope output and temperature stably. The basic component used was MPU6050.<br>
Here is the PCB Layout and Connection<br>
![](https://github.com/Real-time-embedded10/Magic-Music-Player/blob/master/Image/PCB_design.jpg)<br>
For further information and instruction about PCB Design please [click here](https://github.com/Real-time-embedded10/Magic-Music-Player/tree/master/Hardware).

[***Software***](https://github.com/Real-time-embedded10/Magic-Music-Player/tree/master/Software)<br>
Our Software contains three parts: Digital Signal Processing, Hand Gesture Recognition and Communication.<br>
![](https://github.com/Real-time-embedded10/Magic-Music-Player/blob/master/Image/Software.jpg)<br>

[*Digital Signal Processing*](https://github.com/Real-time-embedded10/Magic-Music-Player/tree/master/Software/Digital%20Signal%20Processing)<br>
[image]<br>
[introduction]<br>

[*Hand Gesture Recognition*](https://github.com/Real-time-embedded10/Magic-Music-Player/tree/master/Software/Hand%20Gesture%20Recognition)<br>
![](https://github.com/Real-time-embedded10/Magic-Music-Player/blob/master/Image/HandGesture_Result.jpg)<br>
[Here is C++ code](https://github.com/Real-time-embedded10/Magic-Music-Player/tree/master/Software/Hand%20Gesture%20Recognition/Real%20Time%20Recognition%20System) that use Raspberry pi to recognize hand gesture in real time. <br>
Besides, a [DATABASE](https://github.com/Real-time-embedded10/Magic-Music-Player/tree/master/Software/Hand%20Gesture%20Recognition/DATABASE), including 6 hand gestures, is established. <br>
Codes used to [machine learning model training](https://github.com/Real-time-embedded10/Magic-Music-Player/tree/master/Software/Hand%20Gesture%20Recognition/Software%20Used%20in%20Database%20Establishment) and [model testing](https://github.com/Real-time-embedded10/Magic-Music-Player/tree/master/Software/Hand%20Gesture%20Recognition/Software%20Used%20in%20Testing) are also avaiable in this Repository.<br>

[*Wireless Communication*](https://github.com/Real-time-embedded10/Magic-Music-Player/tree/master/Software/Wireless%20Communication)<br>
Wireless communication uses TCP-based Socket communication between the Raspberry Pi and the PC in the local area network. Here, the Raspberry Pi is used as the server and the PC as the client. After the connection, the server sends information to the client.<br>

[***UI Design***](https://github.com/Real-time-embedded10/Magic-Music-Player/tree/master/UI%20software)<br>

[image]<br>


Authors
--
**tashanguanyan** - Xinyun Jiang (2227272J): I2C system, Hand Gesture Recognition (Database Establishment, Machine Learning Model Training and Real-time Recoginition System).<br>
**YangDING0201** - Yang Ding (2492952D): UI MusicPlayer for PC & Rasberry Pi (UI design and Digital Signal Processing), UI Communication.<br>
**LianfengWu** - Lianfeng Wu (2227370W): Hardware(PCB Design), Wireless Communication. <br>
<br>
Please follow us [Twitter](https://twitter.com/MusicTeam10).<br>




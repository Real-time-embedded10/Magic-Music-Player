Magic-Music-Player
==
This project aims to design a real-time gesture-based Magic Music System, capable of adding sound effects (including tone and/or volume) in real time using defined hand gestures.

Introduction
--
**Main Function**<br>
Export source from PC; <br>
Equipped control UI on PC; <br>
Recognise Hand Gesture in real time; <br>
Change music tone/volume by gestures in the process of playing music.<br>

**Hardware**<br>
Graphical User Interface: PC<br>
Sensors of Hand Gesture: Accelerometer<br>
Real-time Hand Gesture Recognition: Raspberry Pi<br>

**Software**<br>
Marchine learning model to classify hand gestures.<br>
Digital signal processing algorithm to process input song.<br>
Communication system to realize wireless connection bewteen PC and respberry pi.<br>

Our Work
--
[**Hardware**](https://github.com/Real-time-embedded10/Magic-Music-Player/tree/master/Hardware)

[PCB image]<br>

[**Software**](https://github.com/Real-time-embedded10/Magic-Music-Player/tree/master/Software)<br>

[Flow Chart]<br>

Our Software contains three parts:<br>
[*Digital Signal Processing*](https://github.com/Real-time-embedded10/Magic-Music-Player/tree/master/Software/Digital%20Signal%20Processing)
[image]<br>
[introduction]<br>

[*Hand Gesture Recognition*](https://github.com/Real-time-embedded10/Magic-Music-Player/tree/master/Software/Hand%20Gesture%20Recognition)<br>
[image]<br>
[Here](https://github.com/Real-time-embedded10/Magic-Music-Player/tree/master/Software/Hand%20Gesture%20Recognition/Real%20Time%20Recognition%20System) is C++ code that use Raspberry pi to recognize hand gesture in real time. <br>
Besides, a [database](https://github.com/Real-time-embedded10/Magic-Music-Player/tree/master/Software/Hand%20Gesture%20Recognition/DATABASE), including 6 hand gestures, is established. <br>
Codes used to [machine learning model training](https://github.com/Real-time-embedded10/Magic-Music-Player/tree/master/Software/Hand%20Gesture%20Recognition/Software%20Used%20in%20Database%20Establishment) and [model testing](https://github.com/Real-time-embedded10/Magic-Music-Player/tree/master/Software/Hand%20Gesture%20Recognition/Software%20Used%20in%20Database%20Establishment) are also avaiable in this Repository.<br>



[*Wireless Communication*](https://github.com/Real-time-embedded10/Magic-Music-Player/tree/master/Software/Wireless%20Communication)


Contributors
--
Xinyun Jiang (2227272J): Hand Gesture Recognition.<br>
Yang Ding (): UI Design, Digital Signal Processing, Communication. <br>
Lianfeng Wu (): Hareware Design, Communication. <br>





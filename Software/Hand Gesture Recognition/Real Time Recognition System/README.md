Real Time Recognition System
==
Here are four demos (unit tests) provided to show how to acheive each stage of the proposed system to recognize gesture on Raspberry pi in real time. <br>
To obtain detail explanation about, for example, why we do this process or how to determine parameters, please see our [wiki](https://github.com/Real-time-embedded10/Magic-Music-Player/tree/master/Software/Hand%20Gesture%20Recognition/Software%20Used%20in%20Database%20Establishment).<br>

Requirement
--
[WiringPi library](http://wiringpi.com/)<br>
```
sudo apt-get install wiringpi
```
MPU6050_demo
--
This demo is used to show how to achieve data collection in real time at 20Hz sampling rate. <br>
```
while (sample_time - last_sample_time < 50) {
            sample_time = millis();
}
last_sample_time = sample_time;
```
Sampling rate can change, but it’s better not to do this, or almost all the parameters of the subsequent processing (such as segmentation) need to be modified, and a new machine learning model should be re-trained. 20Hz is a great sampling rate, according to the results of our many tests.<br>
<br>
Make sure that files: `CMakeLists.txt`, `MPU6050_Registers.h`, `MPU6050_Types.h`, `MPU6050.h`, `MPU6050.cpp` and `MPU6050_demo.cpp` are in one folder. <br>

Segmentation_demo
--
This demo is used to show how to achieve hand segmentation in real time, and record 30 useful data of each axis for each gesture. <br>
```
seg.SegmentationProcess(xa, ya, za, xg, yg, zg);
if (seg.GestureDetectResult == 1) {
    std::cout << "YES" << std::endl;
}
```
Make sure that files: `CMakeLists.txt`, `MPU6050_Registers.h`, `MPU6050_Types.h`, `MPU6050.h`, `MPU6050.cpp`, `Segmentation.h`,`Segmentation.cpp` and `Segmentation_demo.cpp` are in one folder. <br>

FeatureExtraction_demo
--
This demo is used to show how to achieve feature extraction in real time, and extract 21 key features for each gesture. <br>
```
fea.extractionProcess(seg.recordTargetXA, seg.recordTargetYA, seg.recordTargetZA, seg.recordTargetXG, seg.recordTargetYG, seg.recordTargetZG);
```
Make sure that files: `CMakeLists.txt`, `MPU6050_Registers.h`, `MPU6050_Types.h`, `MPU6050.h`, `MPU6050.cpp`, `Segmentation.h`,`Segmentation.cpp`, `FeatureExtraction.h`, `FeatureExtraction.cpp` and `FeatureExtraction_demo.cpp` are in one folder. <br>

Classification_demo
--
This demo is used to show how to recognize gesture in real time, and the correspondence between classification results and gestures is as follows. <br>
```
cla.classify(fea.extractedFeature);
std::cout << cla.classificationResult << std::endl;
```
|ClassificationResult|   Gesture   |
|--------------------|-------------|
|         1          |   Forward   |
|         2          |   Backward  |
|         3          |    Left     |
|         4          |    Right    |
|         5          |     Up      |
|         6          |    Down     |
<br>

Make sure that files: `CMakeLists.txt`, `MPU6050_Registers.h`, `MPU6050_Types.h`, `MPU6050.h`, `MPU6050.cpp`, `Segmentation.h`,`Segmentation.cpp`, `FeatureExtraction.h`, `FeatureExtraction.cpp`, `Classification.h`, `Classification.cpp` and `Classification_demo.cpp` are in one folder. <br>

Run the demo
--
```
cmake .
make
./main
```
Tests
--
Two cross validation methods are proposed to test classification successful rate. Please [click here](https://github.com/Real-time-embedded10/Magic-Music-Player/tree/master/Software/Hand%20Gesture%20Recognition/Software%20Used%20in%20Testing)

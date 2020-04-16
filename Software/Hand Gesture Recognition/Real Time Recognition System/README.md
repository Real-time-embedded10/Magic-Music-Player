Real Time Recognition System
==
Here are four demos provided to show how to acheice each stage of the proposed system to recognize gesture in real time. <br>

Requirement
--
[WiringPi library](http://wiringpi.com/)<br>

    sudo apt-get install wiringpi<br>

MPU6050_demo
--
This demo is used to show how to achieve data collection in real time at 20Hz sampling rate. <br>
<br>
Make sure that files: `CMakeLists.txt`, `MPU6050_Registers.h`, `MPU6050_Types.h`, `MPU6050.h`, `MPU6050.cpp` and `MPU6050_demo.cpp` are in one folder. <br>
Then <br>
        cmake .
        make
        ./main

Segmentation_demo
--
This demo is used to show how to achieve hand segmentation in real time, and record 30 useful data of each axis for each gesture. <br>
<br>
Make sure that files: `CMakeLists.txt`, `MPU6050_Registers.h`, `MPU6050_Types.h`, `MPU6050.h`, `MPU6050.cpp`, `Segmentation.h`,`Segmentation.cpp` and `Segmentation_demo.cpp` are in one folder. <br>
Then <br>
        cmake .
        make
        ./main

FeatureExtraction_demo
--
This demo is used to show how to achieve feature extraction in real time, and extract 21 features for each gesture. <br>
<br>
Make sure that files: `CMakeLists.txt`, `MPU6050_Registers.h`, `MPU6050_Types.h`, `MPU6050.h`, `MPU6050.cpp`, `Segmentation.h`,`Segmentation.cpp`, `FeatureExtraction.h`, `FeatureExtraction.cpp` and `FeatureExtraction_demo.cpp` are in one folder. <br>
Then <br>
        cmake .
        make
        ./main

Classification_demo
--
This demo is used to show how to recognize gesture in real time, and the correspondence between classification results and gestures is as follows. <br>
<br>
|ClassificationResult|   Gesture   |
|--------------------|-------------|
|         1          |   Forward   |
|         2          |   Backward  |
|         3          |    Left     |
|         4          |    Right    |
|         5          |     Up      |
|         6          |    Down     |
<br>
Make sure that files: `CMakeLists.txt`, `MPU6050_Registers.h`, `MPU6050_Types.h`, `MPU6050.h`, `MPU6050.cpp`, `Segmentation.h`,`Segmentation.cpp`, `FeatureExtraction.h`, `FeatureExtraction.cpp` and `FeatureExtraction_demo.cpp` are in one folder. <br>
Then <br>
        cmake .
        make
        ./main

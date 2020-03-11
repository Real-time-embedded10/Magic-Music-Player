Introduction
--
A real-time sensor-based dynamic hand gesture recognition system in raspberry pi, capable of automatically identifying whether a gesture is inputted and then translating it in the form of text, is introduced. <br>

Proposed System
--
The process of gesture recognition can be categorized into four stages, namely data acquisition, pre-processing, features extraction and classification. The input data of the system is acquired from accelerometer sensor (MPU6050), and then pre-processed to find the Region of Interest (ROI), where hand gesture is, for further processing. This stage is also called hand gesture segmentation. Features extraction is a stage whereby using some statistical features from time domain to complete the transformation of segmented gesture data into sets of feature vector. Afterwards, for classification, machine learning is used to model the selected features, mapping them to a specific hand gesture.<br>

DATABASE
--
A database containing six gestures (forward, backward, right, left, up and down) was built, including a total of 1,080 samples played by six signers (30 samples pre gesture pre person). <br>
The original data and pre-processed database are shown in folder 'DATABASE'. <br>

Software Used in Database Establishment
--
In the folder 'Software Used in Database Establishment', all code used in the process of establishing database, analysing data and training the machine learning model is introduced. All anaysis work was finished on PC, using JetBrains PyCharm and MATLAB. The aim of all of files in this folder is to find a practical process methond (for example, what parameters are better for segmentation, which features are useful for classification, etc.) that can be used in the final real-time program. <br>

Software Used in Testing
--
The purpose of files in folder "Software Used in Testing" is to test the successful identification rate of the result of "Software Used in Database Establishment".<br>

Real Time Recognition System
--
After completing a great processing method and trained model, the final real-time recognition system is mentioned in folder "Real Time Recognition System". It can segment, process and then classify gestures in real time. <br>

Note
--
All code written in python and MATLAB is only used for data pre-analysis or model training. Only code in C++ is written for raspberry pi to achieve the final goal in real time.

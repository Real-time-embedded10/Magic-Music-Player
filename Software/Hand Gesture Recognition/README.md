Note
--
All code written in python and MATLAB is only used for data pre-analysis or model training. Only code in C++ is written for raspberry pi to achieve the final goal in real time.<br>
<br>

Introduction
--
A real-time sensor-based dynamic hand gesture recognition system in raspberry pi, capable of automatically identifying whether a gesture is inputted and then translating it in the form of text, is introduced. <br>

The work is summarized as follows.<br>
>* A database containing six gestures (forward, backward, right, left, up and down) was built, of which 30 samples played by 6 people were mapped for each gesture. Therefore, in our database, there are a total of 1,080 samples.<br>
>* A method that can automatically determine whether a gesture is inputted and segment useful information was developed, and it tries to reduce noise interference as much as possible.<br> 
>* By using several statistical algorithms, 21 features were extracted to represent each original sample, which reduces the computational complexity and increases classification successful rate.<br>
>* Using supervised machine learning algorithms, a classifier model was established which can complete classification effectively in a relatively short time.<br>

<br>
Here are four folders, which are DATABASE, Real Time Recognition System, Software Used in Database Establishment and Software Used in Testing.<br>
<br>
In folder `DATABASE` , original data of these six gestures collected from sensor and pre-processed database used for machine learning model training are available.<br>
In folder `Real Time Recognition System` , four demos and relevant source files about how to use proposed system to recognize gesture in real time are offered. All programs are written in C++ and implemented on the Raspberry Pi. <br>
In folder `Software Used in Database Establishment` , more detailed theoretical introduction about the proposed system is provided, and all code used in the process of establishing database, analysing data and training the machine learning model is introduced. All anaysis work was finished on PC, using JetBrains PyCharm and MATLAB. The aim of these files in this folder is to find a practical process methond (for example, what parameters are better for segmentation, which features are useful for classification, etc.) that can be used in the final real-time program. <br>
In folder `Software Used in Testing` , the purpose is to test the successful identification rate of the result of "Software Used in Database Establishment". These work was also implemented on PC, using JetBrains PyCharm.<br>

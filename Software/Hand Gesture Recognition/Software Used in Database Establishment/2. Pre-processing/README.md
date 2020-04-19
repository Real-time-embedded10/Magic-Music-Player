Pre-processing
--
The work of pre-processing is for the purpose of removing unwanted noise or useless (static) gesture as much as possible and remaining enough useful gesture information. In this step, the Region of Interest (interested hand area) for each gesture is preliminarily segmented as a 30x6 matrix, including 30 data of six axises respectively.<br>
![](https://github.com/Real-time-embedded10/Magic-Music-Player/blob/master/Software/Hand%20Gesture%20Recognition/Software%20Used%20in%20Database%20Establishment/2.%20Pre-processing/Segmented_Samples.jpg)<br>

File `Data_Analysis.m` is used as a tool to determine segmentation parameters, and segmentation process is achieved in file `Segmentation.py`. <br>
For the complete pre-processed database, please [clike here](https://github.com/Real-time-embedded10/Magic-Music-Player/tree/master/Software/Hand%20Gesture%20Recognition/DATABASE/Pre_processed%20Data).

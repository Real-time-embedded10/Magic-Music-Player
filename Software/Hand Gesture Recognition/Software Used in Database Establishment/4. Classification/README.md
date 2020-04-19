Classification
--
A supervised training method is implemented. File `Model_Training.m` is used to calculate **weight gradient matrix** and **bias gradient matrix**, which will be used to establish classifier. <br> 

Feature vector of one gesture sample is a 1 * 21 matrix. The aim of classifier is to transform this feature vector into a 6 * 1 result matrix.<br>
```
Result Matrix A[6][1] = Weight Matrix w[6][1] * Feature Vector f[1][21] + Bias Matrix b[6][1]
```
If the six gestures that need to be classified are defined as 1 to 6, the position of the maximum value of the result matrix is the prediction result of the classifier. For example, if the result matrix is [0.9974, 0, 0, 0.0026, 0, 0.0007], the prediction result is the first gesture: forward movement. <br> 

The increased number of iteration will decrease the value of loss step by step and almost reach zero eventually. To achieve transformation process, 2000 iteration is used to train the model with the collected dataset and obtained expected [weight martix](https://github.com/Real-time-embedded10/Magic-Music-Player/blob/master/Software/Hand%20Gesture%20Recognition/Software%20Used%20in%20Database%20Establishment/4.%20Classification/weight_gradient_matrix.xlsx) and [bias martix](https://github.com/Real-time-embedded10/Magic-Music-Player/blob/master/Software/Hand%20Gesture%20Recognition/Software%20Used%20in%20Database%20Establishment/4.%20Classification/bias_gradient_matrix.xlsx). <br>

![](https://github.com/Real-time-embedded10/Magic-Music-Player/blob/master/Software/Hand%20Gesture%20Recognition/Software%20Used%20in%20Database%20Establishment/4.%20Classification/loss-number%20of%20iteration.jpg)
 
 

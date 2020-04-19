Classification
--
A supervised training method is implemented. File `Model_Training.m` is used to calaculate **weight gradient matrix** and **bias gradient matrix**, which will be used to establish classifier. <br> 

Feature vector of one gesture sample is a 1 * 21 matrix. The aim of classifier is to transform this feature vector into a 6 * 1 result matrix, by Equation 1. <br>
Result Matrix A[6][1] = Weight Matrix w[6][1] * Feature Vector f[1][21] + Bias Matrix b[6][1]. (1) <br>

If the six gestures that need to be classified are defined as 1 to 6, the position of the maximum value of the result matrix is the prediction result of the classifier. For example, if the result matrix is [0.9974 0 0 0.0026 0 0.0007], the prediction result is the first gesture: forward movement. <br> 

To achieve this transformation process, 2000 iteration is used to train the model with the collected dataset and obtained expected weight martix and bias martix. <br>
 
 

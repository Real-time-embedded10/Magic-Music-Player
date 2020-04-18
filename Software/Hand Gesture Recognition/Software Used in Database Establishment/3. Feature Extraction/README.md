Feature Extraction
==
Introduction
--
For each gesture, 180 samples were collected, and for each sample, there are 30 * 6 = 180 data values which should be processed. 
To decrease the computational complexity, the feature extraction technique is implemented. <br>
In gesture recognition, the extracted features should contain relevant information from gesture input, 
which serves as an identity to be classified separately from other gestures.
A set of the following statistical features from time domain is derived from the data vector:<br>

>* Five basic elementary statistics variables are used. 
They are mean, median, variance, standard deviation and difference (between the maximum and minimum):
the former two represent the average level of a set of data, 
and the latter three are statistics describing the degree of dispersion of data.<br>
>* Skewness of the signal of each axis, equation 1. By comparing the sample with the normal (symmetrical) distribution,
 it measures the asymmetry situation of the sample. Values far from zero means the skewed degree and its signal reflects the direction.<br>
> ![](https://github.com/Real-time-embedded10/Magic-Music-Player/blob/master/Software/Hand%20Gesture%20Recognition/Software%20Used%20in%20Database%20Establishment/3.%20Feature%20Extraction/Features%20Equation/skewness.jpg)(1)<br>
, where Si is the ith sampled signal, N is the number of values in one period, and μ is the mean.<br>
>* Kurtosis of the signal of each axis, equation 2. 
 High Kurtosis means that the increase of variance is caused by some extreme values of low probability, 
 which is much greater or less than the average value. 
 It provides a measure of how peaked or flat the probability distribution of the spectrum is. 
 If it is greater than three, the shape of the peak is steeper than that of the normal distribution. <br>
>![](https://github.com/Real-time-embedded10/Magic-Music-Player/blob/master/Software/Hand%20Gesture%20Recognition/Software%20Used%20in%20Database%20Establishment/3.%20Feature%20Extraction/Features%20Equation/kurtosis.jpg)(2)<br>
, where μ is the mean.<br>
>* Correlation coefficient of the signal between any two axes of the sensor, equation 3. 
 It is a measure of the correlation between two variables. It is used to find the relationship between different axes.<br>
>![](https://github.com/Real-time-embedded10/Magic-Music-Player/blob/master/Software/Hand%20Gesture%20Recognition/Software%20Used%20in%20Database%20Establishment/3.%20Feature%20Extraction/Features%20Equation/correlation%20coefficient.jpg)(3)<br>
, where COV(x,y) is the covariance of signals of x axis and y axis, Var(x) is the variance of signal of x-axis and Var(y) is of y-axis.<br>
 >* Average of the 7th to 10th data and the 12th to 16th data. 
 After comparing differences among these six gestures samples, 
 the part from 7th to 10th data and the part form the 12th to 16th data are usually important.<br>
 
 Evaluation
 --
62 features were evaluated, and please [click here](https://github.com/Real-time-embedded10/Magic-Music-Player/blob/master/Software/Hand%20Gesture%20Recognition/Software%20Used%20in%20Database%20Establishment/3.%20Feature%20Extraction/analyse_feature.m) to obtain revelant codes. Evaluation result is shown as follows. <br>
`a:` accelerometer; `g:` gyroscope; <br>
`xa:` x-axis of accelerometer; `ya:` y-axis of accelerometer; `za:` z-axis of accelerometer; <br>
`xg:` x-axis of gyroscope; `yg:` x-axis of gyroscope; `zg:` z-axis of gyroscope. <br>
`1 - 5:` Very poor - Very great
| Feature | Score | Feature | Score | Feature | Score |
|---------|-------|---------|-------|---------|-------|
|mean of xa|3|median of xa|3|variance of xa|1|
|standard deviation of xa|4|difference of xa|4|
|mean of ya|2|median of ya|1|variance of ya|1|
|standard deviation of ya|4|difference of ya|4|
|mean of za|2|median of za|3|variance of za|1|
|standard deviation of za|4|difference of za|4|
|mean of xg|1|median of xg|2|variance of xg|1|
|standard deviation of xg|2|difference of xg|1|
|mean of yg|1|median of yg|1|variance of yg|1|
|standard deviation of yg|2|difference of yg|1|
|mean of zg|1|median of zg|2|variance of zg|1|
|standard deviation of zg|4|difference of zg|3|
|skewness of xa|2|kurtosis of xa|1|skewness of ya|1|kurtosis of ya|1|
|skewness of za|1|kurtosis of za|1|skewness of xg|1|kurtosis of xg|1|
|skewness of yg|1|kurtosis of yg|1|skewness of zg|3|kurtosis of zg|3|
|cor-coefficient of xa and ya|1|cor-coefficient of xa and za|1|cor-coefficient of ya and za|1|
|cor-coefficient of xg and yg|1|cor-coefficient of xg and zg|3|cor-coefficient of yg and zg|1|
|mean cor-coefficient of a|3|mean cor-coefficient of g|2|
|weighted-mean1 of xa|4|weighted-mean2 of xa|5|weighted-mean1 of ya|4|weighted-mean2 of ya|5|
|weighted-mean1 of za|4|weighted-mean2 of za|4|weighted-mean1 of xg|1|weighted-mean2 of xg|1|
|weighted-mean1 of yg|1|weighted-mean2 of yg|1|weighted-mean1 of zg|1|weighted-mean2 of zg|1|

Feature Selection
--
Finally, 21 features were selected. They are:
|Number|Feature|
|------|-------|
|1 |   mean of xa|
|2 |   median of xa|
|3 |   standard deviation of xa|
|4 |   difference of xa|
|5 |   standard deviation of ya|
|6 |   difference of ya|
|7 |   median of za|
|8 |   standard deviation of za|
|9 |   difference of za|
|10|   standard deviation of zg|
|11|   difference of zg|
|12|   skewness of zg|
|13|   kurtosis of zg|
|14|   mean of correlation coefficient of accelerometer|
|15|   correlation coefficient of x-axis and z-axis of gyroscope|
|16|   average of the 7th to 10th data of xa|
|17|   average of the 12th to 16th data of xa|
|18|   average of the 7th to 10th data of ya|
|19|   average of the 12th to 16th data of ya|
|20|   average of the 7th to 10th data of za|
|21|   average of the 12th to 16th data of za|

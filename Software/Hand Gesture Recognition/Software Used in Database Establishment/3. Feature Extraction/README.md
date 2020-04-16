Feature Extraction
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
,where Si is the ith sampled signal, N is the number of values in one period, and μ is the mean.<br>
>* Kurtosis of the signal of each axis, equation 2. 
 High Kurtosis means that the increase of variance is caused by some extreme values of low probability, 
 which is much greater or less than the average value. 
 It provides a measure of how peaked or flat the probability distribution of the spectrum is. 
 If it is greater than three, the shape of the peak is steeper than that of the normal distribution. <br>
>![](https://github.com/Real-time-embedded10/Magic-Music-Player/blob/master/Software/Hand%20Gesture%20Recognition/Software%20Used%20in%20Database%20Establishment/3.%20Feature%20Extraction/Features%20Equation/kurtosis.jpg)(2)<br>
,where μ is the mean.<br>
>* Correlation coefficient of the signal between any two axes of the same sensor, equation 3. 
 It is a measure of the correlation between two variables. It is used to find the relationship between different axes.<br>
>![](https://github.com/Real-time-embedded10/Magic-Music-Player/blob/master/Software/Hand%20Gesture%20Recognition/Software%20Used%20in%20Database%20Establishment/3.%20Feature%20Extraction/Features%20Equation/correlation%20coefficient.jpg)(3)<br>
,where COV(x,y) is the covariance of signals of x axis and y axis, Var(x) is the variance of signal of x-axis and Var(y) is of y-axis.<br>
 >* Average of the 7th to 10th data and the 12th to 16th data. 
 After comparing differences among these six gestures samples, 
 the part from 7th to 10th data and the part form the 12th to 16th data are usually important.<br>

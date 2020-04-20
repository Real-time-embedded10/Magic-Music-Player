#include "FeatureExtraction.h"

/* a1, a2, a3, g1, g2, g3 are segmented hand gesture information, and each one includes 30 data of one axis.
*  a1 | a2 | a3 | g1 | g2 | g3 
* ----+----+----+----+----+----
*  xa | ya | za | xg | yg | zg
*/
void FEATUREEXTRACTION::extractionProcess(float* a1, float* a2, float* a3, float* g1, float* g2, float* g3) {
	feature(a1, a2, a3, g1, g2, g3);
}

/* Function of calculating 7 statistical features.
Thay are mean, median, difference (between the maximum and minimum), variance, standard deviation, skewness and kurtosis of one axis.
*/
void FEATUREEXTRACTION::featureSet(float* A) {
	float sum = 0;
	float min = A[0];
	float max = A[0];
	float mean = 0;
	float median = 0;
	float diff = 0;
	float var = 0;
	float std = 0;
	float skew = 0;
	float kurt = 0;

	for (int i = 0; i < 30; i++) {
		sum = sum + A[i];
		if (min > A[i]) {
			min = A[i];
		}
		if (max < A[i]) {
			max = A[i];
		}
	}
	mean = sum / 30;
	median = (A[14] + A[15]) / 2;
	diff = max - min;

	for (int i = 0; i < 30; i++) {
		var = var + pow(A[i] - mean, 2);
	}
	var = var / 29;
	std = pow(var, 0.5);

	for (int i = 0; i < 30; i++) {
		skew = skew + pow((A[i] - mean)/std, 3);
		kurt = kurt + pow(A[i] - mean, 4);
	}
	skew = skew / 30;
	kurt = (kurt / 30) / pow(var * 29 / 30, 2) - 3;
		
	output1[0] = mean;
	output1[1] = median;
	output1[2] = diff;
	output1[3] = var;
	output1[4] = std;
	output1[5] = skew;
	output1[6] = kurt;
}

/* Function of calculating correlation coefficient of the signal between any two axes of the sensor. */
float FEATUREEXTRACTION::correlation(float* A, float* B) {
	float cx = 0;
	float cy = 0;
	float cxy = 0;
	float mean_x = 0;
	float mean_y = 0;
	for (int i = 0; i < 30; i++) {
		mean_x = mean_x + A[i];
		mean_y = mean_y + B[i];
	}
	mean_x = mean_x / 30;
	mean_y = mean_y / 30;
	for (int i = 0; i < 30; i++) {
		cxy = cxy + (A[i] - mean_x) * (B[i] - mean_y);
		cx = cx + pow(A[i] - mean_x, 2);
		cy = cy + pow(B[i] - mean_y, 2);
	}
	cxy = cxy / pow(cx, 0.5) / pow(cy, 0.5);
	return cxy * 100;
}

/* Function of calculating mean of correlation coefficient. */
float FEATUREEXTRACTION::correlationXYZ(float* A, float* B, float* C) {
	float correlationXY = correlation(A, B);
	float correlationYZ = correlation(B, C);
	float correlationXZ = correlation(A, C);
	return (correlationXY + correlationYZ + correlationXZ) / 3;
}

/* Function of average of the 7th to 10th data and the 12th to 16th data. */
void FEATUREEXTRACTION::weightedAverage(float* A) {
	float mean1;
	float mean2;
	for (int i = 7; i < 11; i++) {
		mean1 = mean1 + A[i];
	}
	mean1 = mean1 / 4;
	for (int i = 12; i < 17; i++) {
		mean2 = mean2 + A[i];
	}
	mean2 = mean2 / 5;
	output1[7] = mean1;
	output1[8] = mean2;
}

/* Calculate and extract useful features for further processing (classification). 
* extractedFeature |                            Feature
* -----------------+------------------------------------------------------------
*       [0]        |   mean of xa 
*       [1]        |   median of xa 
*       [2]        |   standard deviation of xa
*       [3]        |   difference of xa
*       [4]        |   standard deviation of ya
*       [5]        |   difference of ya
*       [6]        |   median of za
*       [7]        |   standard deviation of za
*       [8]        |   difference of za
*       [9]        |   standard deviation of zg
*       [10]       |   difference of zg
*       [11]       |   skewness of zg
*       [12]       |   kurtosis of zg
*       [13]       |   mean of correlation coefficient of accelerometer
*       [14]       |   correlation coefficient of x-axis and z-axis of gyroscope
*       [15]       |   average of the 7th to 10th data of xa
*       [16]       |   average of the 12th to 16th data of xa
*       [17]       |   average of the 7th to 10th data of ya
*       [18]       |   average of the 12th to 16th data of ya
*       [19]       |   average of the 7th to 10th data of za
*       [20]       |   average of the 12th to 16th data of za
* Further information about why choose these features is available at
* Magic-Music-Player/Software/Hand Gesture Recognition/Software Used in Database Establishment/3. Feature Extraction/
*/
void FEATUREEXTRACTION::feature(float* XA, float* YA, float* ZA, float* XG, float* YG, float* ZG){
	featureSet(XA);
	extractedFeature[0] = output1[0];
	extractedFeature[1] = output1[1];
	extractedFeature[2] = output1[4];
	extractedFeature[3] = output1[2];
	featureSet(YA);
	extractedFeature[4] = output1[4];
	extractedFeature[5] = output1[2];
	featureSet(ZA);
	extractedFeature[6] = output1[1];
	extractedFeature[7] = output1[4];
	extractedFeature[8] = output1[2];
	featureSet(ZG);
	extractedFeature[9] = output1[4];
	extractedFeature[10] = output1[2];
	extractedFeature[11] = output1[5];
	extractedFeature[12] = output1[6];
	extractedFeature[13] = correlationXYZ(XA, YA, ZA);
	extractedFeature[14] = correlation(XG, ZG);
	weightedAverage(XA);
	extractedFeature[15] = output1[7];
	extractedFeature[16] = output1[8];
	weightedAverage(YA);
	extractedFeature[17] = output1[7];
	extractedFeature[18] = output1[8];
	weightedAverage(ZA);
	extractedFeature[19] = output1[7];
	extractedFeature[20] = output1[8];
}

#include "FeatureExtraction.h"


void FEATUREEXTRACTION::extractionProcess(float* a1, float* a2, float* a3, float* g1, float* g2, float* g3) {
	feature(a1, a2, a3, g1, g2, g3);
}

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

float FEATUREEXTRACTION::correlationXYZ(float* A, float* B, float* C) {
	float correlationXY = correlation(A, B);
	float correlationYZ = correlation(B, C);
	float correlationXZ = correlation(A, C);
	return (correlationXY + correlationYZ + correlationXZ) / 3;
}

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
#ifndef _FeatureExtraction_H_
#define _FeatureExtraction_H_

#include <stdio.h>
#include <iostream>
#include <cmath>
#include "math.h"

class FEATUREEXTRACTION {
public:
	float extractedFeature[21];

	void extractionProcess(float*, float*, float*, float*, float*, float*);
	void featureSet(float*);
	float correlation(float*, float*);
	float correlationXYZ(float*, float*, float*);
	void weightedAverage(float*);
	void feature(float*, float*, float*, float*, float*, float*);

private:
	float a1, a2, a3, g1, g2, g3;
	float output1[8];
};

#endif



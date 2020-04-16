#ifndef _Segmentation_H_
#define _Segmentaiton_H_

#include <stdio.h>
#include <iostream>
#include <cmath>

class SEGMENTATION {
public:
    void initialize(float, float, float, float, float, float);
    void SegmentationProcess(float, float, float, float, float, float);
    void recordSampleData();
    void judgeInputType();
    void inputGestureDetect();
    void recordTarget();
    int GestureDetectResult; // 1: Have Geature; 0: No Geasture  
    float recordTargetData[30][6];  //The result of hand segmentaion which will be used for feature extraction.
    int judgeInputResult;

private:
    float inputa1, inputa2, inputa3, inputg1, inputg2, inputg3;
    float a1, a2, a3, g1, g2, g3;
    int judgeResultOld[30];
    int judgeResultNew[30];
    float recordSampleOld[30][6];
    float recordSampleNew[30][6];
};

#endif
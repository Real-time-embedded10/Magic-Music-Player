#include "Segmentation.h"

/* inputa1, inputa2, inputa3, inputg1, inputg2, inputg3 are real-time data read from sensor.
*  a1 | a2 | a3 | g1 | g2 | g3 
* ----+----+----+----+----+----
*  xa | ya | za | xg | yg | zg
* When detecting gesture input, run recordTarget().
*/
void SEGMENTATION::SegmentationProcess(float inputa1, float inputa2, float inputa3, float inputg1, float inputg2, float inputg3) {
    initialize(inputa1, inputa2, inputa3, inputg1, inputg2, inputg3);
    recordSampleData();
    judgeInputType();
    inputGestureDetect();
    if (GestureDetectResult == 1) {
        recordTarget();
    }
}

/* Pre-process information read from sensor for better detection result. */
void SEGMENTATION::initialize(float inputa1, float inputa2, float inputa3, float inputg1, float inputg2, float inputg3) {
    a1 = inputa1 * 150;
    a2 = inputa2 * 300;
    a3 = inputa3 * 100;
    g1 = inputg1 * 10;
    g2 = inputg2 * 10;
    g3 = inputg3 * 10;
}

/* Record information read from sensor in one period (1.8s), including 30 data for each axis. 
* recordSampleNew[30][6] will be updated whenever new data is read from the sensor.
*/
void SEGMENTATION::recordSampleData() {
    recordSampleNew[29][0] = a1;
    recordSampleNew[29][1] = a2;
    recordSampleNew[29][2] = a3;
    recordSampleNew[29][3] = g1;
    recordSampleNew[29][4] = g2;
    recordSampleNew[29][5] = g3;
    for (int j = 0; j < 6; j++) {
        for (int i = 0; i < 29; i++) {
            recordSampleNew[i][j] = recordSampleOld[i + 1][j];
        }
    }
    for (int j = 0; j < 6; j++) {
        for (int i = 0; i < 30; i++) {
            recordSampleOld[i][j] = recordSampleNew[i][j];
        }
    }
}

/* Detect large change of data, and the result will be used to detect whether a gesture is. 
*  judgeInputResult |        0        |         1 
* ------------------+-----------------+-------------------
*                   | No large change | Have large change
*/
void SEGMENTATION::judgeInputType() {
    judgeInputResult = 0; 
    if (-700 < a1 && a1 < 700 && -700 < a2 && a2< 700 && 700 < a3 && a3 < 2200 && -700 < g1 && g1 < 700 && -700 < g2 && g2 < 700 && -700 < g3 && g3 < 700) {
        judgeInputResult = 0;
    }else {
        judgeInputResult = 1;
    }
}

/* Identify whether the gesture is.
This algorithm tries to reduce the noise interference as much as possible.
GestureDetectResult = 1: Here is a gesture!
*/
void SEGMENTATION::inputGestureDetect() {
    GestureDetectResult = 0;
    judgeResultNew[29] = judgeInputResult;
    for (int i = 0; i < 29; i++) {
        judgeResultNew[i] = judgeResultOld[i+1];
    }
    for (int i = 0; i < 30; i++) {
        judgeResultOld[i] = judgeResultNew[i];
    }
    int sumTest = 0;
    for (int i = 0; i < 20; i++) {
        sumTest = sumTest + judgeResultNew[i];
    }
    if (sumTest == 0 && judgeResultNew[20] == 1 && judgeResultNew[21] + judgeResultNew[22] != 0) {
        GestureDetectResult = 1;
    }
}

/* When there is a gesture, 
* recordTargetData is used to record useful information of this gesture as segmentation result 
* which will be used for feature extraction.
*/
void SEGMENTATION::recordTarget() {
    for (int i = 0; i < 30; i++) {
        recordTargetXA[i] = recordSampleNew[i][0];
        recordTargetYA[i] = recordSampleNew[i][1];
        recordTargetZA[i] = recordSampleNew[i][2];
        recordTargetXG[i] = recordSampleNew[i][3];
        recordTargetYG[i] = recordSampleNew[i][4];
        recordTargetZG[i] = recordSampleNew[i][5];
    }
}

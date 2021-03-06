//
// Created by peilin on 2019/10/2.
//

#ifndef OPERATOR_CASCADE_CLASSIFER_H
#define OPERATOR_CASCADE_CLASSIFER_H

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

class cascade_classifer {
public:

    cascade_classifer();
    ~cascade_classifer();
    vector<Rect> faces(Mat frame);
    vector<Rect> eyes(Mat frame);

private:
    FileStorage config;
    CascadeClassifier face_cascade;
    CascadeClassifier eyes_cascade;
    String FACE_MODEL_PATH;
    String EYES_MODEL_PATH;
    int FACE_MINS;
    float FACE_OVERLAP_RATE;
    bool isOverlap(Rect rct1, Rect rct2);
};


#endif //OPERATOR_CASCADE_CLASSIFER_H

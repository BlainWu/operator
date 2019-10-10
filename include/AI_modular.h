//
// Created by peilin on 2019/10/4.
//

#ifndef OPERATOR_AI_MODULAR_H
#define OPERATOR_AI_MODULAR_H

#include<iostream>
#include <opencv2/core.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;
using namespace cv::dnn;

class AI_modular {

public:
    AI_modular();
    ~AI_modular();
    void predict_age(Mat image);
    void predict_gender(Mat image);
    int face_recognize(Mat image);

private:
    FileStorage config;
    Net age_net;
    Net gender_net;
    Net face_recognize_net;
    String FACE_MODEL;
    String AGE_MODEL,AGE_TEXT;
    String GENDER_MODEL,GENDER_TEXT;
    int COMMON_THICKNESS,OPERATOR_THICKNESS;
    vector<String> ages;
    vector<String> operators;
    float FONT_SIZE;
};


#endif //OPERATOR_AI_MODULAR_H
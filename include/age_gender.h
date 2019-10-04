//
// Created by peilin on 2019/10/4.
//

#ifndef OPERATOR_AGE_GENDER_H
#define OPERATOR_AGE_GENDER_H

#include<iostream>
#include <opencv2/core.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;
using namespace cv::dnn;

class age_gender {

public:
    age_gender();
    ~age_gender();
    void predict_age(Mat image);
    void predict_gender(Mat image);

private:
    FileStorage config;
    Net age_net;
    Net gender_net;
    String AGE_MODEL,AGE_TEXT;
    String GENDER_MODEL,GENDER_TEXT;
    vector<String> ages;
    float FONT_SIZE;
};


#endif //OPERATOR_AGE_GENDER_H

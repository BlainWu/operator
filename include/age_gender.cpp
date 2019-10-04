//
// Created by peilin on 2019/10/4.
//

#include "age_gender.h"

age_gender::age_gender():config("../config/config_sys.yaml",FileStorage::READ)
{
    GENDER_MODEL = (String)config["gender_model"];
    GENDER_TEXT = (String)config["gender_text"];
    AGE_MODEL = (String)config["age_model"];
    AGE_TEXT = (String)config["age_text"];
    FONT_SIZE = (float)config["age_gender_font_size"];
    age_net=readNetFromCaffe(AGE_TEXT,AGE_MODEL);
    gender_net=readNetFromCaffe(GENDER_TEXT,GENDER_MODEL);

    //init vector ages
    ages.push_back("0-3");
    ages.push_back("4 - 7");
    ages.push_back("8 - 14");
    ages.push_back("12 - 18");
    ages.push_back("18 - 21");
    ages.push_back("21 - 27");
    ages.push_back("48 - 53");
    ages.push_back("60-");


}
age_gender::~age_gender()
{

}

void age_gender::predict_age(Mat image)
{
    //change mat data to binary large object
    Mat blob = blobFromImage(image,1.0,Size(227,227));
    //push the blob to the net
    age_net.setInput(blob,"data");
    Mat prob = age_net.forward("prob");
    Mat probMat = prob.reshape(1,1);

    Point classNum;
    double classProb;

    //calculate the max probability
    minMaxLoc(probMat,NULL,&classProb,NULL,&classNum);
    int classidx = classNum.x;

    putText(image, format("age:%s", ages.at(classidx).c_str()), Point(2, 20),
            FONT_HERSHEY_PLAIN, FONT_SIZE, Scalar(0, 0, 255), 2);
}

void age_gender::predict_gender(Mat image)
{
    Mat blob = blobFromImage(image, 1.0, Size(227, 227));
    gender_net.setInput(blob, "data");
    //预测分类
    Mat prob = gender_net.forward("prob");
    Mat probMat = prob.reshape(1, 1);

    //保证要么是male 要么是female，promat。at（0,0）或者（0,1）
    putText(image, format("gender:%s", (probMat.at<float>(0, 0) > probMat.at<float>(0, 1) ? "Male" : "Female")),
            Point(2, 40), FONT_HERSHEY_PLAIN, FONT_SIZE, Scalar(0, 0, 255), 2);
}
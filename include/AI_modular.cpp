//
// Created by peilin on 2019/10/4.
//

#include "AI_modular.h"

AI_modular::AI_modular(): config("../config/config_sys.yaml", FileStorage::READ)
{
    //load perameters
    GENDER_MODEL = (String)config["gender_model"];
    GENDER_TEXT = (String)config["gender_text"];
    AGE_MODEL = (String)config["age_model"];
    AGE_TEXT = (String)config["age_text"];
    COMMON_THICKNESS=(int)config["common_thickness"];
    OPERATOR_THICKNESS=(int)config["operator_thickness"];
    FONT_SIZE = (float)config["age_gender_font_size"];
    age_net=readNetFromCaffe(AGE_TEXT,AGE_MODEL);
    gender_net=readNetFromCaffe(GENDER_TEXT,GENDER_MODEL);
    //FACE_MODEL=(String)config["tf_model"];
    //FACE_PBTXT=(String)config["tf_txt"];
    //face_recognize_net=readNetFromTensorflow(FACE_MODEL,FACE_PBTXT);
    //init vector ages
    ages.push_back("0-3");
    ages.push_back("4 - 7");
    ages.push_back("8 - 14");
    ages.push_back("12 - 18");
    ages.push_back("18 - 21");
    ages.push_back("21 - 27");
    ages.push_back("48 - 53");
    ages.push_back("60-");

/*    operators.push_back("operator1");
    operators.push_back("operator2");
    operators.push_back("operator3");
    operators.push_back("operator4");*/

}
AI_modular::~AI_modular()
{

}

void AI_modular::predict_age(Mat image)
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

    putText(image, format("%s", ages.at(classidx).c_str()), Point(2, 20),
            FONT_HERSHEY_PLAIN, FONT_SIZE, Scalar(0, 0, 255), COMMON_THICKNESS);
}

void AI_modular::predict_gender(Mat image)
{
    Mat blob = blobFromImage(image, 1.0, Size(227, 227));
    gender_net.setInput(blob, "data");
    //预测分类
    Mat prob = gender_net.forward("prob");
    Mat probMat = prob.reshape(1, 1);

    //保证要么是male 要么是female，promat。at（0,0）或者（0,1）
    putText(image, format("%s", (probMat.at<float>(0, 0) > probMat.at<float>(0, 1) ? "Male" : "Female")),
            Point(2, 40), FONT_HERSHEY_PLAIN, FONT_SIZE, Scalar(0, 0, 255),
            COMMON_THICKNESS);
}

/*
int AI_modular::face_recognize(Mat image)
{

   Mat blob = blobFromImage(image,1.0,Size(64,64));
    face_recognize_net.setInput(blob,"data");
    Mat prob = face_recognize_net.forward("prob");
    Mat probMat = prob.reshape(1,1);

    Point classNum;
    double classProb;

    minMaxLoc(probMat,NULL,&classProb,NULL,&classNum);
    int classidx = classNum.x;

    return classidx;

}
*/
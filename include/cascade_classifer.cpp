//
// Created by peilin on 2019/10/2.
//

#include "cascade_classifer.h"

cascade_classifer::cascade_classifer(): config("../config/config_sys.yaml", FileStorage::READ)
{
    FACE_MODEL_PATH = (String)config["face_model_path"];
    EYES_MODEL_PATH = (String)config["eyes_model_path"];
    face_cascade.load(FACE_MODEL_PATH);
    eyes_cascade.load(EYES_MODEL_PATH);

}
cascade_classifer::~cascade_classifer()
{

}

int cascade_classifer::faces(Mat frame)
{
    //init and preproce
    size_t num ;
    if(frame.empty())
        cout<<"No image in frame!"<<endl;
    vector<Rect> faces;
    Mat frame_gray;
    cvtColor(frame,frame_gray,COLOR_BGR2GRAY);
    //detect
    face_cascade.detectMultiScale(frame_gray, faces);
    Point a,b;
    for(num = 0;num<faces.size();num++)
    {
        rectangle(frame,cvPoint(faces[num].x,faces[num].y),cvPoint(faces[num].x+faces[num].width,faces[num].y+faces[num].height),Scalar(255,0,0));
    }

    return (int)faces.size();
}

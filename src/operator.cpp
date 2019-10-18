#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include "../include/cascade_classifer.h"
#include "../include/AI_modular.h"
// #include "../include/Motor_Control.h"
#include <opencv2/face.hpp>
#include <unistd.h>

using namespace cv::face;
using namespace cv;
using namespace std;



int main(int argc,char ** argv)
{
    //读取参数文件
    FileStorage config("../config/config_sys.yaml",FileStorage::READ);
    if(config.isOpened())
        cout<<"Load config data succssfully!"<<endl;
    else
    {
        cout << "Load config data failed!" << endl;
        return -1;
    }
    //加载参数
    size_t people_num= (int)config["people_num"];
    int CAM=(int)config["camera_num"],FPS=(int)config["FPS"];
    String face_recognize_model=(String)config["face_recognize"];
    String position;
    int face_flag=0,face_id,operator_id,people_top=0,people_low=0,operator_location=1;
    double probability=0,max_probability=0;


    //初始化摄像头
    VideoCapture cap;
    cap.open(CAM);
    if ( ! cap.isOpened() )
    {
        cout << "--(!)Error opening video capture\n";
        return -1;
    }

    int WIDTH=cap.get(CV_CAP_PROP_FRAME_WIDTH);
    int HEIGHT=cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 2560);//宽度
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 1920);//高度
    cap.set(CV_CAP_PROP_FPS,FPS);


    //初始化类和模型
    cascade_classifer cascade;
    AI_modular AI;
//    Motor_Control MC;
    ofstream put;
    put.open("../result/description.txt",ios::app);

    Ptr<face::FaceRecognizer> model = face::FisherFaceRecognizer::create();
    model->read(face_recognize_model);

    Mat frame;

    vector<Rect> faces;

    while(true)
       {
           cap>>frame;
           resize(frame,frame,Size(640,480));
           faces = cascade.faces(frame);



           if(faces.size()!=1)
               continue;

           if(faces[0].width<68 || faces[0].height<68)
                continue;
           face_flag++; // 检测单人脸次数

           if(face_flag<20)
               continue;

           Mat predict_face=frame(faces[0]);
           resize(predict_face,predict_face,Size(64,64));
           cvtColor(predict_face,predict_face,CV_RGB2GRAY);

           face_id = model->predict(predict_face);
           putText(frame,"Operator",Point(faces[0].x, faces[0].y),FONT_HERSHEY_PLAIN,2,Scalar(0, 0, 255),2);

           imwrite("../result/operator.png",frame);

//           MC.buzzer(600);

           break;
       }

    cout<<"Detect operator!"<<endl;

    sleep(10);

//    MC.buzzer(200);
//    MC.turn_back(175);


    while(true)
    {
        cap>>frame;
        faces = cascade.faces(frame);
        if(faces.size()!=people_num)
        {
            continue;
        }

        for(size_t t =0;t<faces.size();t++)
        {
            Mat temp_face=frame(faces[t]);
            resize(temp_face,temp_face,Size(64,64));
            cvtColor(temp_face,temp_face,CV_RGB2GRAY);

            model->predict(temp_face,face_id,probability);
            if(probability>max_probability)
            {
                max_probability=probability;
                operator_id=t;
            }
            AI.predict_age(frame(faces[t]));
            AI.predict_gender(frame(faces[t]));

        }
        rectangle(frame, cvPoint(faces[operator_id].x, faces[operator_id].y),
                  cvPoint(faces[operator_id].x + faces[operator_id].width,
                          faces[operator_id].y + faces[operator_id].height),
                  Scalar(0,255, 0),2);
        putText(frame,"Operator",Point(faces[operator_id].x, faces[operator_id].y),FONT_HERSHEY_PLAIN,2,Scalar(0, 255, 0),2);

        for(size_t t =0;t<faces.size();t++)
        {
            if(faces[t].x<faces[operator_id].x)
                operator_location++;
            if(faces[t].y<faces[people_top].y)
                people_top=t;
            if(faces[t].y>faces[people_low].y)
                people_low=t;
        }

        if((faces[operator_id].y-faces[people_top].y) < (faces[people_low].y-faces[operator_id].y))
            position = "standing";
        else
            position = "sitting";

        putText(frame,position,Point(faces[operator_id].x, faces[operator_id].y-20),FONT_HERSHEY_PLAIN,2,Scalar(0, 255, 0),2);

        if(position=="standing")
        {
            put<<"操作员站在左数第"<<operator_location<<"个."<<endl;
            cout<<"操作员站在左数第"<<operator_location<<"个."<<endl;
        }
        else
            {
                put<<"操作员坐在左数第"<<operator_location<<"个."<<endl;
                cout<<"操作员坐在左数第"<<operator_location<<"个."<<endl;

            }

        imwrite("../result/crowds.png",frame);

        break;
    }

//    MC.buzzer(1000);

}

/*
     Mat p3;
    Mat temp1,temp2;
    vector<Rect> v3;
    String str;
    p3=imread("../2.JPG");

    v3=cascade.faces(p3);

    cout<<v3.size()<<endl;
    for(size_t t = 0;t<v3.size();t++)
    {

        AI.predict_age(p3(v3[t]));
        AI.predict_gender(p3(v3[t]));

        resize(p3(v3[t]),temp1,Size(64,64));
        cvtColor(temp1,temp1,CV_BGR2GRAY);
        equalizeHist(temp1, temp1);
        switch (model->predict(temp1)) //对每张脸都识别
        {
            case 0:str = "W"; break;
            case 1:str = "WA"; break;
            case 2:str = "LI"; break;
            default: str = "Error"; break;
        }

        cout<<str<<endl;
    }
    imshow("3",p3);
    imwrite("result.jpg",p3);
    waitKey(0);


        while(true)
       {
           cap>>frame;
           faces = cascade.faces(frame);

           for(size_t t = 0;t<faces.size();t++)
           {
               AI.predict_age(frame(faces[t]));
               AI.predict_gender(frame(faces[t]));
           }
           cout<<faces.size()<<endl;;
           cout<<frame.rows<<"  "<<frame.cols<<endl;
           cout<<WIDTH<<" "<<HEIGHT<<endl;
           imshow("cam",frame);
           waitKey(1);
           break;
       }
*/
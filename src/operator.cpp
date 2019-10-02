#include <iostream>
#include <opencv2/opencv.hpp>
#include "../include/cascade_classifer.h"

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
    int CAM=(int)config["camera_num"],FPS=(int)config["FPS"];

    //初始化摄像头
    VideoCapture cap(CAM);
    cap.set(CV_CAP_PROP_FPS,FPS);
    cascade_classifer cascade;
    Mat frame;

    int face_quantity;
    while(true)
    {
        cap>>frame;
        face_quantity = cascade.faces(frame);
        cout<<face_quantity<<endl;;
        imshow("cam",frame);
        waitKey(1);
    }
}




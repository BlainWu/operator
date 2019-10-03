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


/*    Mat p1,p2,p3;
    vector<Rect> v1,v2,v3;
    p1=imread("../1.JPG") ,p2=imread("../2.JPG"),p3=imread("../3.JPG");
    //v1=cascade.faces(p1);
    v2=cascade.faces(p2),v3=cascade.faces(p3);

    cout<<v1.size()<<endl;
    cout<<v2.size()<<endl;
    cout<<v3.size()<<endl;
    //imshow("1",p1);
    imshow("2",p2);
    imshow("3",p3);
    waitKey(0);*/
    vector<Rect> faces;
    while(true)
    {
        cap>>frame;
        faces = cascade.faces(frame);
        cout<<faces.size()<<endl;;
        imshow("cam",frame);
        waitKey(1);
    }
}
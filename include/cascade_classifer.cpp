//
// Created by peilin on 2019/10/2.
//

#include "cascade_classifer.h"

cascade_classifer::cascade_classifer(): config("../config/config_sys.yaml", FileStorage::READ)
{
    FACE_MODEL_PATH = (String)config["face_model_path"];
    EYES_MODEL_PATH = (String)config["eyes_model_path"];
    FACE_OVERLAP_RATE = (float)config["face_overlap_rate"];
    FACE_MINS = (int)config["face_mins"];
    face_cascade.load(FACE_MODEL_PATH);
    eyes_cascade.load(EYES_MODEL_PATH);


}
cascade_classifer::~cascade_classifer()
{

}

vector<Rect> cascade_classifer::faces(Mat frame) {
    //init and preproce
    cascade_classifer cascade;
    size_t num_faces, repeat, repeat_final;
    Mat frame_gray;
    vector<Rect> faces_init, eyes, faces, faces_final;

    if (frame.empty())
        cout << "No image in frame!" << endl;
    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);

    //detect
    face_cascade.detectMultiScale(frame_gray, faces_init, 1.1, FACE_MINS,0,Size(50,50),Size(350,350));

    if(faces_init.size()==0)
        return faces_init;
    else
    {
        faces.push_back(faces_init[0]);
        for(repeat=1;repeat<faces_init.size();repeat++)
        {
            for(repeat_final=0;repeat_final<faces.size();repeat_final++)
            {
                if(cascade.isOverlap(faces_init[repeat], faces[repeat_final]))
                    break;
            }
            if(repeat_final==faces.size())
                faces.push_back(faces_init[repeat]);
            else continue;
        }
    }
        
    for(num_faces=0;num_faces<faces.size();num_faces++)
    {
        eyes=cascade.eyes(frame_gray(faces[num_faces]));
        if(eyes.size())
        {
            faces_final.push_back(faces[num_faces]);
            rectangle(frame, cvPoint(faces[num_faces].x, faces[num_faces].y),
                      cvPoint(faces[num_faces].x + faces[num_faces].width,
                              faces[num_faces].y + faces[num_faces].height),
                      Scalar(255, 0, 0),2);
        }
    }
    return faces_final;
}

vector<Rect> cascade_classifer::eyes(Mat frame)
{
    vector<Rect> eyes_data;
    eyes_cascade.detectMultiScale(frame, eyes_data);
    return eyes_data;
}

bool cascade_classifer::isOverlap(Rect rc1,Rect rc2)
{
    if ((rc1.x + rc1.width*FACE_OVERLAP_RATE)  > rc2.x &&
        (rc2.x + rc2.width*FACE_OVERLAP_RATE)  > rc1.x &&
        (rc1.y + rc1.height*FACE_OVERLAP_RATE) > rc2.y &&
        (rc2.y + rc2.height*FACE_OVERLAP_RATE) > rc1.y
        )
        return true;
    else
        return false;
}
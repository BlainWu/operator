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
    size_t num_faces_pre, num_eye, repeat, repeat_final;
    Mat frame_gray;
    vector<Rect> faces_init, eyes, faces, faces_final;

    if (frame.empty())
        cout << "No image in frame!" << endl;
    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);

    //detect
    face_cascade.detectMultiScale(frame_gray, faces_init, 1.1, FACE_MINS);
    eyes = cascade.eyes(frame_gray);
    for (num_faces_pre = 0; num_faces_pre < faces_init.size(); num_faces_pre++) {
        for (num_eye = 0; num_eye < eyes.size(); num_eye++) {
            if (cascade.eye_on_face(eyes[num_eye], faces_init[num_faces_pre])) {
                rectangle(frame, cvPoint(faces_init[num_faces_pre].x, faces_init[num_faces_pre].y),
                          cvPoint(faces_init[num_faces_pre].x + faces_init[num_faces_pre].width,
                                  faces_init[num_faces_pre].y + faces_init[num_faces_pre].height),
                          Scalar(255, 0, 0),2);
                faces.push_back(faces_init[num_faces_pre]);
            } else continue;
        }
    }
    if(faces.size()==0)
    {
        return faces;
    }
    else
        {
            faces_final.push_back(faces[0]);
            for(repeat=0;repeat<faces.size();repeat++)
            {
                for(repeat_final=0;repeat_final<faces_final.size();repeat_final++)
                {
                    if (!cascade.isOverlap(faces[repeat], faces_final[repeat_final]))
                        continue;
                    else break;
                }
                if(repeat_final==faces_final.size())
                    faces_final.push_back(faces[repeat]);
                else continue;
            }
        }

    return faces_final;
}

vector<Rect> cascade_classifer::eyes(Mat frame)
{
    if(frame.empty())
        cout<<"No image in frame!"<<endl;
    vector<Rect> eyes_data;
    eyes_cascade.detectMultiScale(frame, eyes_data);

    size_t num_eye;
    for(num_eye = 0;num_eye<eyes_data.size();num_eye++)
    {
        rectangle(frame,cvPoint(eyes_data[num_eye].x,eyes_data[num_eye].y),
                cvPoint(eyes_data[num_eye].x+eyes_data[num_eye].width,
                        eyes_data[num_eye].y+eyes_data[num_eye].height),Scalar(0,255,0));
    }
    return eyes_data;
}

bool cascade_classifer::eye_on_face(Rect eye,Rect face)
{
    if(face.x<eye.x && (face.x+face.width)>eye.x && eye.y >face.y && eye.y<(face.y+face.height))
        return true;
    else return false;
}

bool cascade_classifer::isOverlap(Rect rc1,Rect rc2)
{
    if ((rc1.x + rc1.width)*FACE_OVERLAP_RATE  > rc2.x &&
        (rc2.x + rc2.width)*FACE_OVERLAP_RATE  > rc1.x &&
        (rc1.y + rc1.height)*FACE_OVERLAP_RATE > rc2.y &&
        (rc2.y + rc2.height)*FACE_OVERLAP_RATE > rc1.y
        )
        return true;
    else
        return false;
}
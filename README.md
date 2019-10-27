# operator
服务机器人赛题，在识别阶段记住操作员后转身在人群中找到操作员

# 文件夹说明
src：存放主函数
config：参数存放
data：级联分类器\caffe模型
include：自定义的c++类
result: 存放运行结果

# 环境要求
OpenCV >= 3.2
wiringPi（树莓派）

# 可调用的函数
## Motor_Control.h	
void turn_left(); //原地左转
void turn_right();//原地右转
void forward(); //匀速前进
void backward();//匀速后退
void move_stop();//停止
## Cascade_classifer.h
vector<Rect> faces(Mat frame); //返回所有人脸框信息 (x，y,width,height)
vector<Rect> eyes(Mat frame); //返回所有人眼框信息 (x，y,width,height)

# 配置参数 config_sys.yaml
camera_num ：相机序列号 默认0
face_model_path:人脸级联分类器位置
eyes_model_path: 人眼级联分类器位置
face_overlap_rate: 脸部重合率阈值，即两个框重合多少判断为同一个人
face_mins: 每个框扫描n次确定为人脸（默认为3 ，1不准确，2提高速度）

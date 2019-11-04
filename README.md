# operator
服务机器人赛题
# 文件夹说明
src：源代码
config：参数存放
data：检测模型
include：c++类  
result:运行结果

# 环境要求
OpenCV 3 +Contirb模块
wiringPi（树莓派）

# 可引用的函数
## Motor_Control.h
void turn_left(); //原地左转  
void turn_right();//原地右转  
void forward(); //匀速前进  
void backward();//匀速后退  
void move_stop();//停止  
void Motor_Control::turn_back(float angle) //转身一定的角度  
void Motor_Control::buzzer(int time_ms)//蜂鸣器鸣响一定的时间  
## Cascade_classifer.h
vector<Rect> faces(Mat frame); //返回所有人脸框信息 (x，y,width,height)  
vector<Rect> eyes(Mat frame); //返回人眼框信息  
bool isOverlap(Rect rc1,Rect rc2) //判断两个人脸框是否高度（重叠度阈值可设置）  
vector<Rect> Rect_Union(vector<Rect> rc1,vector<Rect> rc2) //取两组矩形容器的并集  
## AI_modeular.h
void predict_age(Mat image)//返回一个年龄判断
void predict_gender(Mat image) //返回一个性别判断

# 配置参数 config_sys.yaml
camera_num ：相机序列号 默认0
face_model_path:人脸级联分类器位置
eyes_model_path: 人眼级联分类器位置
face_overlap_rate: 脸部重合率阈值，即两个框重合多少判断为同一个人
face_mins: 每个框扫描n次确定为人脸（默认为3 ，1不准确，2提高速度）

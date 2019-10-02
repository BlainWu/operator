# operator
服务机器人赛题
# 文件夹说明
src：存放源代码
config：参数存放
data：检测模型
include：c++类

# 环境要求
OpenCV 3
wiringPi（树莓派）

# 可引用的函数
## Motor_Control.h	
  void turn_left(); //原地左转
 	void turn_right();//原地右转
	void forward(); //匀速前进
	void backward();//匀速后退
	void move_stop();//停止


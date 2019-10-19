//
// Created by peilin on 2019/10/2.
//

#include "Motor_Control.h"

Motor_Control::Motor_Control()
{
    wiringPiSetup();
	//陀螺仪初始
    fd = wiringPiI2CSetup (SlaveAddress);  
    if (fd >= 0) { // fd 为负数，说明IIC连接失败
        printf("fd = %d\n",fd);
        wiringPiI2CWriteReg8(fd,PWR_MGMT_1,0x00); // 开启温度检测 关闭休眠
        wiringPiI2CWriteReg8(fd,SMPLRT_DIV, 0x07);
        wiringPiI2CWriteReg8(fd,CONFIG, 0x06);
        wiringPiI2CWriteReg8(fd,GYRO_CONFIG, 0x18);
        wiringPiI2CWriteReg8(fd,ACCEL_CONFIG, 0x01);
    }
    else {
        printf("IIC初始化失败");
    }

    pinMode(4, OUTPUT);//LEFT_FORWARD
    pinMode(0, OUTPUT);//LEFT_BACKWARD
    pinMode(2, OUTPUT);//RIGHT_FORWARD
    pinMode(3, OUTPUT);//RIGHT_BACKWARD
    pinMode(25, OUTPUT);//BUZZER CONTRIAL
    digitalWrite(4,LOW);
    digitalWrite(2,LOW);
    digitalWrite(0,LOW);
    digitalWrite(3,LOW);
	digitalWrite(25,LOW);
}

Motor_Control::~Motor_Control()
{
    digitalWrite(4,LOW);
    digitalWrite(2,LOW);
    digitalWrite(0,LOW);
    digitalWrite(3,LOW);
}

void Motor_Control::turn_left()
{
    //   digitalWrite(0,HIGH);
    digitalWrite(2,HIGH);
}

void Motor_Control::turn_right()
{
    digitalWrite(4,HIGH);
    //digitalWrite(3, HIGH);
}

void Motor_Control::forward()
{
    digitalWrite(4, HIGH);
    digitalWrite(2, HIGH);
}

void Motor_Control::backward()
{
    digitalWrite(0, HIGH);
    digitalWrite(3, HIGH);
}

void Motor_Control::move_stop()
{
    digitalWrite(4,LOW);
    digitalWrite(2,LOW);
    digitalWrite(0,LOW);
    digitalWrite(3,LOW);
}

void Motor_Control::turn_back(float angle)
{
    Motor_Control MC;
    
    int i;
    float Delta_Y=0,Delta_Z=0;
    int Omega_Y0=0,Omega_Z0=0;
    int Omega_Y,Omega_Z;
    
    for(i=0;i<20;i++)
    {
            Omega_Y0+=MC.getData(GYRO_YOUT_H);
            Omega_Z0+=MC.getData(GYRO_ZOUT_H);
            delay(100);
    }
    
    Omega_Y0/=20;
    Omega_Z0/=20;
    
    Omega_Y0-=Omega_Y0<32768?0:65535;
    Omega_Z0-=Omega_Z0<32768?0:65535;
    
    MC.turn_left();

    while(fabs(Delta_Y)< angle &&fabs(Delta_Z)< angle)
    {
            
            Omega_Y=MC.getData(GYRO_YOUT_H);
            Omega_Z=MC.getData(GYRO_ZOUT_H);
            
            Omega_Y-=Omega_Y<32768?0:65535+Omega_Y0;
            Omega_Z-=Omega_Z<32768?0:65535+Omega_Z0;
            
            Omega_Y=abs(Omega_Y)<30?0:Omega_Y;
            Omega_Z=abs(Omega_Z)<30?0:Omega_Z;
                        
            Delta_Y+=Omega_Y*0.05/32768*2400;//the last number 2400 can be changed
            Delta_Z+=Omega_Z*0.05/32768*2400;
            
            printf("Delta_Y=%f\n",Delta_Y);
            printf("Delta_Z=%f\n",Delta_Z);
            printf("\n");
            
            delay(50);
    }

    MC.move_stop();
}

int Motor_Control::getData(int reg_address)
{
    return (wiringPiI2CReadReg8(fd,reg_address) << 8) + 
    wiringPiI2CReadReg8(fd,reg_address + 1);
}

void Motor_Control::buzzer(int time_ms)
{
	digitalWrite(25, HIGH);
	delay(time_ms);
	digitalWrite(25,LOW);
}

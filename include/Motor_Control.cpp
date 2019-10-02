//
// Created by peilin on 2019/10/2.
//

#include "Motor_Control.h"

Motor_Control::Motor_Control()
{
    wiringPiSetup();
    pinMode(7, OUTPUT);//LEFT_FORWARD
    pinMode(0, OUTPUT);//LEFT_BACKWARD
    pinMode(2, OUTPUT);//RIGHT_FORWARD
    pinMode(3, OUTPUT);//RIGHT_BACKWARD
    digitalWrite(7,LOW);
    digitalWrite(2,LOW);
    digitalWrite(0,LOW);
    digitalWrite(3,LOW);
}

Motor_Control::~Motor_Control()
{
    digitalWrite(7,LOW);
    digitalWrite(2,LOW);
    digitalWrite(0,LOW);
    digitalWrite(3,LOW);
}

void Motor_Control::turn_left()
{
    digitalWrite(0,HIGH);
    digitalWrite(2,HIGH);
}

void Motor_Control::turn_right()
{
    digitalWrite(7,HIGH);
    digitalWrite(3, HIGH);
}

void Motor_Control::forward()
{
    digitalWrite(7, HIGH);
    digitalWrite(2, HIGH);
}

void Motor_Control::backward()
{
    digitalWrite(0, HIGH);
    digitalWrite(3, HIGH);
}

void Motor_Control::move_stop()
{
    digitalWrite(7,LOW);
    digitalWrite(2,LOW);
    digitalWrite(0,LOW);
    digitalWrite(3,LOW);
}
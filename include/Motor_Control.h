//
// Created by peilin on 2019/10/2.
//

#ifndef OPERATOR_MOTOR_CONTROL_H
#define OPERATOR_MOTOR_CONTROL_H


class Motor_Control {
public:
    Motor_Control();
    ~Motor_Control();
    void turn_left();
    void turn_right();
    void forward();
    void backward();
    void move_stop();
};


#endif //OPERATOR_MOTOR_CONTROL_H

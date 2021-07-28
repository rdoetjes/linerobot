#ifndef MOTOR_H
#define MOTOR_H

#include <wiringPi.h>

class Motor {

  public:
    Motor(int dir1, int dir2, int pwm);
    void forward(int speed);
    void reverse(int speed);
    void stop();
    ~Motor();

  private:
    int dir1;
    int dir2;
    int pwm;
};

#endif

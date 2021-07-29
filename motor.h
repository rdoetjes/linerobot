#ifndef MOTOR_H
#define MOTOR_H

#include <wiringPi.h>

class Motor {

  public:
    Motor(int dir1, int dir2, int pwm);
    void forward(int speed);
    void reverse(int speed);
    void stop();
    void setSpeed(int speed);
    ~Motor();

  private:
    int dir1;
    int dir2;
    int pwm;
    long map(long x, long in_min, long in_max, long out_min, long out_max);
};

#endif

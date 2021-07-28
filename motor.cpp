#include "motor.h"

Motor::Motor(int dir1, int dir2, int pwm){
  this->dir1 = dir1;
  this->dir2 = dir2;
  this->pwm = pwm;
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(pwm, PWM_OUTPUT);
}

void Motor::forward(int speed){
   digitalWrite(dir1, HIGH);
   digitalWrite(dir2, LOW);
   pwmWrite (pwm, speed);
}

void Motor::reverse(int speed){
   digitalWrite(dir1, LOW);
   digitalWrite(dir2, HIGH);
   pwmWrite(pwm, speed);
}

void Motor::stop(){
   digitalWrite(dir1, LOW);
   digitalWrite(dir2, LOW);
   pwmWrite(pwm, 0);
}

Motor::~Motor(){
  this->stop();
  dir1=dir2=-1;
}

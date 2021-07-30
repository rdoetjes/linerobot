#include "motor.h"

/*
* dir1 is pin for H-Bridge forward direction 
* dir2 is pin for H-Bridge reverse direction
* pwm is hardware pwm pin 
*/
Motor::Motor(int dir1, int dir2, int pwm){
  this->dir1 = dir1;
  this->dir2 = dir2;
  this->pwm = pwm;

  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(pwm, PWM_OUTPUT);
  pwmSetMode(PWM_MODE_MS);
  pwmSetClock(1000); //5kHz
  pwmSetRange(1000);
}

long Motor::map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void Motor::setSpeed(int speed){
   pwmWrite(pwm, map(speed, 0, 100, 0, 1024));
}

void Motor::forward(int speed){
   digitalWrite(dir1, HIGH);
   digitalWrite(dir2, LOW);
   pwmWrite(pwm, map(speed, 0, 100, 0, 1024));
}

void Motor::reverse(int speed){
   digitalWrite(dir1, LOW);
   digitalWrite(dir2, HIGH);
   pwmWrite(pwm, map(speed, 0, 100, 0, 1024));
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

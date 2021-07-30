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

  gpioSetMode(dir1, PI_OUTPUT);
  gpioSetMode(dir2, PI_OUTPUT);
  gpioSetMode(pwm, PI_ALT5);
  gpioPWM(pwm, 0);
}

long Motor::map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void Motor::setSpeed(int speed){
   gpioPWM(pwm, map(speed, 0, 100, 0, 255));
}

void Motor::forward(int speed){
   gpioWrite(dir1, PI_HIGH);
   gpioWrite(dir2, PI_LOW);
   gpioPWM(pwm, map(speed, 0, 100, 0, 255));
}

void Motor::reverse(int speed){
   gpioPWM(dir1, PI_LOW);
   gpioPWM(dir2, PI_HIGH);
   gpioPWM(pwm, map(speed, 0, 100, 0, 255));
}

void Motor::stop(){
   gpioPWM(dir1, PI_LOW);
   gpioPWM(dir2, PI_LOW);
   gpioPWM(pwm, 0);
}

Motor::~Motor(){
  this->stop();
  dir1=dir2=-1;
}

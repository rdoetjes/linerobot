#include <stddef.h>
#include <wiringPi.h>
#include "motor.h"
#include "qtr8d.h"
#include <iostream>
#include <unistd.h>

#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define MAX_SPEED 100

static Motor *m1;
static Motor *m2;
static const int PinsIn[] { 15, 16, 1, 4, 5, 6, 10, 11 };
static QTR8D *lineSensor;

using namespace std;

static void setup(){
  wiringPiSetup();
 
  lineSensor = new QTR8D(PinsIn, sizeof(PinsIn)/sizeof(PinsIn[0]));
	
  m1=new Motor(0, 2, 26); //Pi Pin: 11, 13, 32
  m1->stop();

  m2=new Motor(24, 25, 23); //Pi Pin: 35, 37, 33
  m1->stop();
}

void destruct(){
  delete lineSensor;
  delete m1;
  delete m2;
}

int main(){
  //PID
  static const double KP = 0.0333f;
  static const double KD = 0.00f;
  const int targetLineValue = 3000;
  static double lastError = 0;

  setup();

  m1->forward(900);
  m1->forward(900);

  while(1){
    unsigned int lineValue = lineSensor->readByte();

    double error = (double)lineValue - (double)targetLineValue;

    double adjustment = KP*error + KD*(error - lastError);

    lastError = error;
    
    std::cout << lineValue << " " << error << " " << adjustment  << " m1 speed " << constrain(MAX_SPEED + adjustment, 0, MAX_SPEED) << " m2 speed " << constrain(MAX_SPEED - adjustment, 0, MAX_SPEED) << std::endl;
    usleep(2000);
    m1->setSpeed(constrain(MAX_SPEED + adjustment, 0, MAX_SPEED));
    m2->setSpeed(constrain(MAX_SPEED - adjustment, 0, MAX_SPEED));
  }

  destruct();

  return 0;
}

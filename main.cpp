#include <stddef.h>
#include <wiringPi.h>
#include "motor.h"
#include "qtr8d.h"
#include <iostream>
#include <unistd.h>

#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define MAX_SPEED 50

static Motor *m1;
static Motor *m2;
static const int PinsIn[] { 15, 16, 1, 4, 5, 6, 10, 11 };
static QTR8D *lineSensor;

const int targetLineValue = 4000;

using namespace std;

static void setup(){
  wiringPiSetup();
 
  lineSensor = new QTR8D(PinsIn, sizeof(PinsIn)/sizeof(PinsIn[0]), targetLineValue);
	
  m1=new Motor(2, 0, 26); //Pi Pin: 13, 11, 32
  m1->stop();

  m2=new Motor(24, 25, 23); //Pi Pin: 35, 37, 33
  m2->stop();
}

void destruct(){
  delete lineSensor;
  delete m1;
  delete m2;
}

int main(int argc, char **argv){
  //PID
  static const double KP = (double)100/(double)targetLineValue;
  static const double KD = 0.00f;
  static double lastError = 0;

  setup();

  while(1){
    unsigned int lineValue = lineSensor->readSensorValue();

    if (lineValue == 9000){
      m1->stop();
      m2->stop();
      exit(0);
    }

    double error = (double)lineValue - (double)targetLineValue;

    double adjustment = KP*error + KD*(error - lastError);

    lastError = error;
    if (argc==2 && string(argv[1])=="-d")
      std::cout << lineValue << " " << error << " " << adjustment  
		<< " m1 speed " << constrain(MAX_SPEED + adjustment, 0, MAX_SPEED) 
		<< " m2 speed " << constrain(MAX_SPEED - adjustment, 0, MAX_SPEED) << std::endl;
    
    m1->forward(constrain(MAX_SPEED + adjustment, 0, MAX_SPEED));
    m2->forward(constrain(MAX_SPEED - adjustment, 0, MAX_SPEED));
    usleep(200);
  }

  destruct();

  return 0;
}

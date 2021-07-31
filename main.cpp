#include <stddef.h>
#include "motor.h"
#include "qtr8d.h"
#include <iostream>
#include <unistd.h>
#include <pigpio.h>
#include <pigpiod_if2.h>

#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define MAX_SPEED 50

static Motor *m1;
static Motor *m2;
static const int PinsIn[] { 14, 15, 18, 23, 24, 25, 8, 7 };
static QTR8D *lineSensor;

const int targetLineValue = 4000;

using namespace std;

static void setup(){
  if (gpioInitialise() < 0){
    std::cerr << "could not connect to pigpiod!\n";
    exit(0);
  }

  lineSensor = new QTR8D(PinsIn, sizeof(PinsIn)/sizeof(PinsIn[0]), targetLineValue);
	
  m1=new Motor(27, 17, 12); //Pi Pin: 13, 11, 32
  m1->stop();

  m2=new Motor(19, 26, 13); //Pi Pin: 35, 37, 33
  m2->stop();
}

void destruct(){
  delete lineSensor;
  delete m1;
  delete m2;
}

int main(int argc, char **argv){
  //PID we only use P and D because I works over time and it is too slow to matter
  static const double KP = (double)100/(double)targetLineValue;
  static const double KD = 0.00f;
  static double lastError = 0;

  setup();

  while(1){
    unsigned int lineValue = lineSensor->readSensorValue();

    if (lineValue == 9000){
      std::cout << "FINISH LINE" << std::endl;
      m1->stop();
      m2->stop();
      gpioTerminate();
      destruct();
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
    usleep(200);   //QRT8D settles in 2500uS but 2500uS overshot 200uS seemed to be the golden time out
  }

  destruct();

  return 0;
}

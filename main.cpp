#include <stddef.h>
#include <wiringPi.h>
#include "motor.h"
#include "qtr8d.h"
#include <iostream>
#include <unistd.h>

static Motor *m1;
static Motor *m2;
static int PinsIn[] { 15, 16, 1, 4, 5, 6, 10, 11 };
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
  setup();
	
  while(1){
    cout << lineSensor->readByte() << endl;

    m1->forward(512);
    m2->forward(512);
    usleep(10000);
  }

  destruct();

  return 0;
}

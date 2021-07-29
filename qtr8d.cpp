#include "qtr8d.h"

QTR8D::QTR8D(const int PinsIn[], int size){
  this->PinsIn = PinsIn;
  this->nrPins = size;
  for(int i=0; i<8; i++) {
    pinMode(PinsIn[i], INPUT);
    pullUpDnControl(PinsIn[i], PUD_UP);
  }
}

unsigned int QTR8D::readByte(){
  unsigned int result = 0;

  for (int i=0; i<nrPins; i++) {
   if ( digitalRead(PinsIn[i]) == 1 ) result |= 1 << i;
  }

  return result;
}

QTR8D::~QTR8D(){
  this->PinsIn = nullptr;
}

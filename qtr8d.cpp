#include "qtr8d.h"
#include <iostream>

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
  unsigned int bits = 0;

  for (int i=0; i<nrPins; i++) {
    if ( digitalRead(PinsIn[i]) == 1 ) {
      result += i * 1000;
      bits++;
    }
  }

  if (bits == 1) return result;

  if (bits == 8) return 4000; //handle a crossing as moving straight on

  //when there's more than 1 bit set and the value is higer that 4000 we return the highest value of the set bits (to force early correction)
  if (bits > 1 && result > 4000){
    result = 0;

    for (int i=7; i!=0; i--) {
      if ( digitalRead(PinsIn[i]) == 1 ) {
        result = i * 1000;  
	break; // we can jump out as soon as we found the set bit
      }
    }

    return result;  
  }

 
  //when there's more than 1 bit set and the value is less that 4000 we return the lowest value of the set bits (to force early correction)
  if (bits > 1 && result < 4000){
    result = 0;

    for (int i=0; i<8; i++) {
      if ( digitalRead(PinsIn[i]) == 1 ) {
        result += i * 1000;
        break; // we can jump out as soon as we found the set bit
      }
    }

    return result;
  }

  return 0;
}

QTR8D::~QTR8D(){
  this->PinsIn = nullptr;
}

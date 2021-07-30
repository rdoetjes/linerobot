#include "qtr8d.h"
#include <iostream>

QTR8D::QTR8D(const int PinsIn[], int size, int targetValue){
  this->PinsIn = PinsIn;
  this->nrPins = size;
  this->targetValue = targetValue;

  for(int i=0; i<8; i++) {
    pinMode(PinsIn[i], INPUT);
    pullUpDnControl(PinsIn[i], PUD_UP);
  }
}

int QTR8D::readSensorBits(){
   int sensor = 0;

   for(int i=0; i<8; i++)
     if (digitalRead(PinsIn[i]) == 1) sensor |= 1 << i;
   
   return sensor;  
}

unsigned int QTR8D::nrBitsSet(int n){
  unsigned int count = 0;

  while(n != 0){
    count++;
    n &= n - 1;
  }

  return count;
}

int QTR8D::sensorValueOneBitOn(uint8_t bits){
  int result = 0;
  uint8_t mask = 1;

  for(int i=1; i<8; i++){
    if ( (mask & bits) != 0 ) {
      result += i * 1000;
      break;	//we can break assoon as we found the bit, as there are no more set bits
    }
    mask = mask << 1;
  }

  return result;
}

int QTR8D::sensorValueMultipleBitsOn(uint8_t bits){
  uint8_t mask = 1;
  int result = 0;

  for(int i=0; i<8; i++){
    if ( (mask & bits) != 0 ) 
      result += i * 1000;
    mask = mask << 1;
  }
 
  //get the first msb that is set and convert that to a Value 0-7000
  if (result > targetValue){
    mask = 128;
    result = 0;

    for(int i=8; i!=0; i--){
      if ( (mask & bits) != 0 ) {
        result += i * 1000;
        return result;
      }
      mask = mask >> 1;
    }  
  }

  //get the first lsb that is set and convert that to a Value 0-7000
  if (result < targetValue){
    mask = 1;
    result = 0;

    for(int i=0; i<8; i++){
      if ( (mask & bits) != 0 ) {
        result += i * 1000;
        return result;
      }
      mask = mask << 1;
    }
  }

  return result;
}

unsigned int QTR8D::readSensorValue(){

  uint8_t bits = readSensorBits();
  int bitsSet = nrBitsSet(bits);

  if (bitsSet == 8) return 9000; //special case that you can react upon in your application
  if (bitsSet == 1) return sensorValueOneBitOn(bits);
  if (bitsSet > 1 && bitsSet < 6) return sensorValueMultipleBitsOn(bits);
  
  return 0;
}

QTR8D::~QTR8D(){
  this->PinsIn = nullptr;
}

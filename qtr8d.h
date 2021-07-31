#ifndef QTR8D_H
#define QTR8D_H
#include <pigpiod_if2.h>
#include <pigpio.h>
#include <cstdint>

#define FINISH_LINE 9000
class QTR8D{

  public:
    const int *PinsIn = nullptr;
    int nrPins;

    QTR8D(const int PinsIn[], int size, int targelValue);
    unsigned int readSensorValue();
    int readSensorBits();
    ~QTR8D();

  private:
    int targetValue;
    unsigned int nrBitsSet(int n);
    int sensorValueOneBitOn(uint8_t bits);
    int sensorValueMultipleBitsOn(uint8_t bits);
};

#endif

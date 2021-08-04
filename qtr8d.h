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

    template<typename T>
    int sensorValueOneBitOn(T bits);

    template<typename T>
    int sensorValueMultipleBitsOn(T bits);
};

#endif

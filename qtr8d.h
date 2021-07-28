#ifndef QTR8D_H
#define QTR8D_H
#include <wiringPi.h>

class QTR8D{

  public:
    int *PinsIn = nullptr;
    int nrPins;

    QTR8D(int PinsIn[], int size);
    int readByte();
    ~QTR8D();

  private:

};

#endif

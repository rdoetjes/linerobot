#ifndef QTR8D_H
#define QTR8D_H
#include <wiringPi.h>

class QTR8D{

  public:
    const int *PinsIn = nullptr;
    int nrPins;

    QTR8D(const int PinsIn[], int size);
    unsigned int readByte();
    ~QTR8D();

  private:

};

#endif

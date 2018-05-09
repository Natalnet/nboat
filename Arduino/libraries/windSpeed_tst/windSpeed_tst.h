#ifndef _windSpeed_tst_h
#define _windSpeed_tst_h

//#include <avr/interrupt.h>
//#include <stdint.h>
#include "Arduino.h"
#include <medianFilter.h>
#include "WindData.h"

volatile static int revolutions = 0;

class windSpeed_tst
{
  public:
    windSpeed_tst();
    void read();
    WindData get();
  private:
    WindData _windData;
    float readDirection(int birutaPin = A0);
    float windDirection;
    int windvaneRead;
    void readSpeed();
    float radius = 0.055; //m from center pin to middle of cup
    float mps;
    // read RPM
    int rpm = 0;
    unsigned long lastmillis = 0;
    medianFilter Filter;

    static void rpm_fan();
};
#endif

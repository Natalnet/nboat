#ifndef Compass_h
#define Compass_h

#include "Arduino.h"

class Compass
{
  public:
    Compass(float norte_quadr_buss);
    float get_value();
  private:
    float bussola, heading, soma, _norte_quadr_buss;
    int slaveAddress, i, headingValue, HMC6352Address;
    byte headingData[2];
};

#endif

/*

  Compass.h - Library for getting curent heading from compass.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#ifndef Compass_h
#define Compass_h

#include "Arduino.h"

class Compass
{
  public:
    Compass(float gridNorth = 104.00);
    float readHeading();
  private:
    float heading, sum, _gridNorth;
    int slaveAddress, i, headingValue, HMC6352Address;
    byte headingData[2];

};

#endif

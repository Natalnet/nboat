/*

  Compass_HMC6352.h - Library for getting curent heading from Compass HMC6352.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#ifndef Compass_HMC6352_h
#define Compass_HMC6352_h

#include "Arduino.h"

class Compass_HMC6352
{
  public:
    Compass_HMC6352(float gridNorth = 104.00);
<<<<<<< HEAD
    float readHeading();
  private:
    float heading, sum, _gridNorth;
=======
    void read();
    float getHeading();

  private:
    float _heading, sum, _gridNorth;
>>>>>>> sailboat_mini
    int slaveAddress, i, headingValue, HMC6352Address, numberOfReadings;
    byte headingData[2];

};

#endif

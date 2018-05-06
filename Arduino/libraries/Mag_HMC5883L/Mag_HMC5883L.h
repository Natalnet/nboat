/*

  Mag_HMC5883L.h - Library for getting curent heading from Compass HMC6352.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#ifndef Mag_HMC5883L_h
#define Mag_HMC5883L_h

#include "Arduino.h"
#include "Pose.h"

class Mag_HMC5883L
{
  public:
    Mag_HMC5883L(float gridNorth = 0.0);
    float getHeading();
    void read();
    Pose get();
  private:
    //calibration
    int HMC5883LAddress, _x, _y, _z, _ctrl;
    Pose _magnetometer;
};

#endif

/*

  Razor9DOF.h - Library for getting curent heading from Compass HMC6352.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#ifndef Razor9DOF_h
#define Razor9DOF_h

#include "Arduino.h"
#include "Pose.h"

class Razor9DOF
{
  public:
    Razor9DOF();
    void read();
    Pose getAccelerometer();
    Pose getGyroscope();
    Pose getMagnetometer();

  private:
    Pose _accelerometer;
    Pose _gyroscope;
    Pose _magnetometer;

};

#endif


/*

  OdometrySensors.h - Library for getting curent heading from Compass HMC6352.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#ifndef OdometrySensors_h
#define OdometrySensors_h

#include "Arduino.h"
#include "GPS_EM506.h" //include all sensors libraries available (for odometry)
#include "Compass_HMC6352.h"


class OdometrySensors
{
  public:
    OdometrySensors();
    float checkSensors();
  private:
    GPS_EM506 gps_EM506;
    Compass_HMC6352 compass_HMC6352;
};

#endif

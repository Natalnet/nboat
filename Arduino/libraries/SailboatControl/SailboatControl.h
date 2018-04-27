/*

  SailboatControl.h - Library containing the movement controllers used in Nboat project.
  Created by Davi H. dos Santos, March 31, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#ifndef SailboatControl_h
#define SailboatControl_h

#include "Arduino.h"
#include "Location.h"
#include "GPS_EM506.h"
#include "Mag_HMC5883L.h"
#include "WeatherSensors.h"
#include "ActuatorsDrivers.h"
#include <SD.h>

class SailboatControl
{
  public:
    SailboatControl();
    void rudderHeadingControl(Location target);
    void sailControl();
    float adjustFrame(float angle);
    float P(float currentError);
    float I(float currentError);
    void setDistanceToTarget(float distance);
    float rudderAngleSaturation(float sensor);
  private:
    float _heading, _sp, _currentError, rudderAngle_prior, rudderAngle, I_prior, _cycleTime, _kp, _ki, _starttime, _endtime, _windDir, _sailAngle;
    GPS_EM506 _gps;
    Mag_HMC5883L _compass;
    Location _currentPosition;
    WeatherSensors _windSensors;
    ActuatorsDrivers _actuators;

};

#endif

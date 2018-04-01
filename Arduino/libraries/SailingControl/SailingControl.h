/*

  SailingControl.h - Library containing the movement controllers used in Nboat project.
  Created by Davi H. dos Santos, March 31, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#ifndef SailingControl_h
#define SailingControl_h

#include "Arduino.h"
#include "Location.h"
#include "GPS.h"
#include "Compass.h"
#include "WeatherSensors.h"
#include "ActuatorsDrivers.h"

class SailingControl
{
  public:
    SailingControl();
    void rudderHeadingControl(Location target);
    void sailControl();
    float adjustFrame(float angle);
    float P(float currentError);
    float I(float currentError);
    float rudderAngleSaturation(float sensor);
  private:
    float _heading, _sp, _currentError, rudderAngle_prior, rudderAngle, I_prior, _cycleTime, _kp, _ki, _starttime, _endtime, _windDir, _sailAngle;
    GPS _gps;
    Compass _compass;
    Location _currentPosition;
    WeatherSensors _windSensors;
    ActuatorsDrivers _actuators;

};

#endif

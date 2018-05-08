/*

  SailboatControl.h - Library containing the movement controllers used in Nboat project.
  Created by Davi H. dos Santos, March 31, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#ifndef SailboatControl_h
#define SailboatControl_h

#include "Arduino.h"
#include "SensorManager.h"
#include "SailboatMiniActuatorDrivers.h"
#include "Navigation.h"

class SailboatControl
{
  public:
    SailboatControl(float kp = 1, float ki = 0);
    void rudderHeadingControl(SensorManager *sensors, Location target);
    void sailControl(SensorManager *sensors);
    float adjustFrame(float angle);
    float P(float currentError);
    float I(float currentError);
    void setDistanceToTarget(float distance);
    float rudderAngleSaturation(float sensor);
  private:
    float _heading, _sp, _currentError, rudderAngle_prior, rudderAngle, I_prior, _cycleTime, _kp, _ki, _starttime, _endtime, _windDir, _sailAngle;
    Location _currentPosition;
    SailboatMiniActuatorDrivers *_actuators;
    Navigation nav;

};

#endif

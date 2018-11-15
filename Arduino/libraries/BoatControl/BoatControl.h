/*

  BoatControl.h - Library containing the movement controllers used in Nboat project.
  Created by Davi H. dos Santos, March 31, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#ifndef BoatControl_h
#define BoatControl_h

#include "Arduino.h"
#include "Location.h"
#include "wqboatActuatorDrivers.h"
#include "SensorManager.h"
#include "NavigationFunctions.h"

class BoatControl
{
  public:
    BoatControl(float kp = 1, float ki = 0);
    void rudderHeadingControl(SensorManager *sensors, Location target);
    void rudderVelocityControl(SensorManager *sensors, Location target);
    void thrusterControl(SensorManager *sensors, Location target);
    void thrusterControlWind(SensorManager *sensors);
    void rudderRCControl(SensorManager *sensors, double rudderPWM);
    void thrusterRCControl(SensorManager *sensors, double thrusterPWM);
    float P(float currentError);
    float I(float currentError);
    void setDistanceToTarget(float distance);
    float rudderAngleSaturation(float sensor);
    void initThruster();
  private:
    float _heading, _sp, _currentError, rudderAngle_prior, rudderAngle, I_prior, _cycleTime, _kp, _ki, _starttime, _endtime, _distanceToTarget;
    Location _currentPosition;
    wqboatActuatorDrivers *_actuators;
    float _mediumDistance = 10.0, _closeDistance = 3.0;
    NavigationFunctions _navFunc;
};

#endif

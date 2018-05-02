/*

  SailboatMiniActuatorDrivers.h - Library for the low level commands to put the Actuator in a desired position.
  Created by Davi H. dos Santos, March 31, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#ifndef SailboatMiniActuatorDrivers_h
#define SailboatMiniActuatorDrivers_h

#include "Arduino.h"
#include "Servo.h"

class SailboatMiniActuatorDrivers
{
  public:
    SailboatMiniActuatorDrivers(int rudderPin = 9, int sailPin = 8);

    void setRudderAngle(float sailAngle);
    void setSailAngle(float sailAngle);

    float getRudderAngle();
    float getSailAngle();    
  private:
    Servo rudder, sail;
    int _rudderPin, _sailPin;
    float _rudderLowerLimit, _rudderUpperLimit, _sailLowerLimit, _sailUpperLimit;
};

#endif

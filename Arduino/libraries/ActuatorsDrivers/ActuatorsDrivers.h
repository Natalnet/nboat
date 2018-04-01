/*

  ActuatorsDrivers.h - Library for the low level commands to put the actuators in a desired position.
  Created by Davi H. dos Santos, March 31, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#ifndef ActuatorsDrivers_h
#define ActuatorsDrivers_h

#include "Arduino.h"
#include "DualVNH5019MotorShield.h"

class ActuatorsDrivers
{
  public:
    ActuatorsDrivers();
    void setSailPosition(float sailAngle, int analogAtuador = A4);
    void setRudderPosition(float rudderAngle);
  private:
    float sensorReading, desiredPosition, _sailAngleMaxValue, sensorError;
    int sailUpperLimit, sailLowerLimit;
    DualVNH5019MotorShield _md;

};

#endif

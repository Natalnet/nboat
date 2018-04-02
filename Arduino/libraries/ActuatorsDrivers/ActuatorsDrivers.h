/*

  ActuatorsDrivers.h - Library for the low level commands to put the actuators in a desired position.
  Created by Davi H. dos Santos, March 31, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#ifndef ActuatorsDrivers_h
#define ActuatorsDrivers_h

#include "Arduino.h"
#include "DualVNH5019MotorShield.h" //actuators driver
#include "Adafruit_TCS34725.h" //collor sensor

class ActuatorsDrivers
{
  public:
    ActuatorsDrivers();
    void setSailPosition(float sailAngle, int sensorPin = A4);
    void setRudderPosition(float rudderAngle);
    int angleToColor(float sensor);
    void getRudderPosition();
    void moveRudder(int desiredColor);
    void readColor();
    void moveRudderToCenter();
    void readCurrentRGB();
  private:
    float sensorReading, desiredPosition, _sailAngleMaxValue, sensorError;
    float _id, _aux, _decpart, lux, r_red, r_green, r_blue;
    int sailUpperLimit, sailLowerLimit;
    int _command, _currentColor;
    uint16_t clear, red, green, blue;
    DualVNH5019MotorShield _sailActuator, _rudderActuator;
    Adafruit_TCS34725 tcs;

};

#endif

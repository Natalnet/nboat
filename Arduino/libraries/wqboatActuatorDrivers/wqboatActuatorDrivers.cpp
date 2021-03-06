/*

  wqboatActuatorDrivers.h - Library for the low level commands to put the actuators (sail and rudder) in a desired position.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/


#include "Arduino.h"
#include "wqboatActuatorDrivers.h"

wqboatActuatorDrivers::wqboatActuatorDrivers(int rudderPin, int thrusterPin){

  _rudderPin = rudderPin;
  _thrusterPin = thrusterPin;

  rudder.attach(_rudderPin);
  thruster.attach(_thrusterPin);
}

wqboatActuatorDrivers::wqboatActuatorDrivers(){
  rudder.attach(_rudderPin);
  thruster.attach(_thrusterPin);
}

void wqboatActuatorDrivers::setRudderAngle(float rudderAngle){
  rudderAngle = constrain(rudderAngle, -90, 90);
  rudderAngle = map(rudderAngle, -90, 90, _rudderLowerLimit, _rudderUpperLimit);
  rudder.write(rudderAngle);
  //delay(50);

  /*if(cont % 5){
    rudder.write(rudderAngle/5);
    Serial.print("SERVO ANGLE: ");
    Serial.println(rudderAngle);
  } else {
    rudderAngle += rudderAngle;
    cont++;
  }*/
  //delay(10000);
}

void wqboatActuatorDrivers::setThrusterPower(float thrusterPower){
  thrusterPower = constrain(thrusterPower, 0, 100);
  thrusterPower = map(thrusterPower, 0, 100, _thrusterLowerLimit, _thrusterUpperLimit);
  thruster.write(thrusterPower);
}

void wqboatActuatorDrivers::initThruster(){
  //rudder.write((_rudderLowerLimit + _rudderUpperLimit)/2);
  thruster.write(10);
  //delay(3000);
}

float wqboatActuatorDrivers::getRudderAngle(){
  return map(rudder.read(), _rudderLowerLimit, _rudderUpperLimit, -90, 90);
}

float wqboatActuatorDrivers::getThrusterPower(){
  return map(thruster.read(), _thrusterLowerLimit, _thrusterUpperLimit, 0, 100); 
}

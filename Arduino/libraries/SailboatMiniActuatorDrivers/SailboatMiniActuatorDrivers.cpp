/*

  SailboatMiniActuatorDrivers.h - Library for the low level commands to put the Actuator (sail and rudder) in a desired position.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/


#include "Arduino.h"
#include "SailboatMiniActuatorDrivers.h"

SailboatMiniActuatorDrivers::SailboatMiniActuatorDrivers(int rudderPin, int sailPin){

  _rudderPin = rudderPin;
  _sailPin = sailPin;

  rudder.attach(_rudderPin);
  sail.attach(_sailPin);

}

SailboatMiniActuatorDrivers::SailboatMiniActuatorDrivers(){
  rudder.attach(_rudderPin);
  sail.attach(_sailPin);
}

void SailboatMiniActuatorDrivers::setSailAngle(float sailAngle){
  sailAngle = constrain(sailAngle, 0, 90);
  sailAngle = map(sailAngle, 0, 90, _sailLowerLimit, _sailUpperLimit);
  sail.write(sailAngle);
}

void SailboatMiniActuatorDrivers::setRudderAngle(float rudderAngle){
  rudderAngle = constrain(rudderAngle, -90, 90);
  rudderAngle = map(rudderAngle, -90, 90, _rudderLowerLimit, _rudderUpperLimit);
  rudder.write(rudderAngle);
}

//transform from servo angle to sail angle
float SailboatMiniActuatorDrivers::getSailAngle(){
<<<<<<< HEAD
  return map(sail.read(), _sailLowerLimit, _sailUpperLimit, 0, 90);
=======
  float servoAngle = sail.read();
  return map(servoAngle, _sailLowerLimit, _sailUpperLimit, -90, 90);
}

float SailboatMiniActuatorDrivers::getSailServo(){
  return sail.read();
>>>>>>> sailboat_mini
}

//transform from servo angle to rudder angle
float SailboatMiniActuatorDrivers::getRudderAngle(){
  float servoAngle = rudder.read();
  return map(servoAngle, _rudderLowerLimit, _rudderUpperLimit, -90, 90);
}

float SailboatMiniActuatorDrivers::getRudderServo(){
  return rudder.read();
}

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
  //delay(10000);
}

void SailboatMiniActuatorDrivers::setRudderAngle(float rudderAngle){
  rudderAngle = constrain(rudderAngle, -90, 90);
  rudderAngle = map(rudderAngle, -90, 90, _rudderLowerLimit, _rudderUpperLimit);
//  Serial.print("SERVO ANGLE: ");
//  Serial.println(rudderAngle);
  rudder.write(rudderAngle);
  //delay(10000);
}

//transform from servo angle to sail angle
float SailboatMiniActuatorDrivers::getSailAngle(){
  return map(sail.read(), _sailLowerLimit, _sailUpperLimit, 0, 90);
}

//transform from servo angle to rudder angle
float SailboatMiniActuatorDrivers::getRudderAngle(){
  return map(rudder.read(), _rudderLowerLimit, _rudderUpperLimit, -90, 90);
}

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

   //TODO calibrate
  _rudderLowerLimit = 50;  //-90 degrees
  _rudderUpperLimit = 110; //-90 degrees

  //TODO calibrate
  _sailLowerLimit = 980; //0 degrees
  _sailUpperLimit = 350; //90 degrees

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

float SailboatMiniActuatorDrivers::getSailAngle(){
  return sail.read();
}

float SailboatMiniActuatorDrivers::getRudderAngle(){
  return rudder.read();
}

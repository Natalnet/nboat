/*

  Razor9DOF.cpp - Library for getting curent heading from Compass model HMC6352.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/


#include "Arduino.h"
#include "Razor9DOF.h"

Razor9DOF::Razor9DOF(){
}

void Razor9DOF::read(){

  Serial2.begin(9600);

  //get accelerometer  
  while (Serial2.available() <= 0) {
      Serial2.println("#vg");
    int time = millis();
    while((millis()-time) < 20){}
  }
  
  if(Serial2.available() > 2) {
   
    _accelerometer.x = Serial2.parseInt();
    _accelerometer.y = Serial2.parseInt();
    _accelerometer.z = Serial2.parseInt();
   
  }

 //get magnetometer  
  while (Serial2.available() <= 0) {
     Serial2.println("#vm");
    int time = millis();
    while((millis()-time) < 20){}
  }
  
  if(Serial2.available() > 2) {
   
    _magnetometer.x = Serial2.parseInt();
    _magnetometer.y = Serial2.parseInt();
    _magnetometer.z = Serial2.parseInt();
   
  }

 //get gyroscope  
  while (Serial2.available() <= 0) {
      Serial2.println("#va");
    int time = millis();
    while((millis()-time) < 20){}
  }
  
  if(Serial2.available() > 2) {
   
    _gyroscope.x = Serial2.parseInt();
    _gyroscope.y = Serial2.parseInt();
    _gyroscope.z = Serial2.parseInt();
   
  }

  Serial2.end(); 
}

Pose Razor9DOF::getAccelerometer(){
  return _accelerometer;
}

Pose Razor9DOF::getGyroscope(){
  return _gyroscope;
}

Pose Razor9DOF::getMagnetometer(){
  return _gyroscope;
}

/*

  IMU_RAZOR.cpp - Library for getting curent heading from Compass model HMC6352.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/


#include "Arduino.h"
#include "IMU_RAZOR.h"

IMU_RAZOR::IMU_RAZOR(){
}

void IMU_RAZOR::read(){
  Serial2.begin(57600);
  
  static float call[4];
  while (Serial2.available() <= 0) {
    Serial2.println("#f");
  }
  delay(50);
  if(Serial2.available() > 2) {
  
    call[0] = Serial2.parseFloat();
    call[1] = Serial2.parseFloat();
    call[2] = Serial2.parseFloat();
    call[3] = Serial2.parseFloat();
  
    Serial2.end();
  }
  _imuData.eulerAngles.yaw = call[0];
  _imuData.eulerAngles.pitch = call[1];
  _imuData.eulerAngles.roll = call[2];
  _imuData.heading = call[3];
}

IMUData IMU_RAZOR::get(){
  return _imuData;
}

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
  
  static float call[3];
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
  _yaw = call[0];
  _pitch = call[1] + 360;
  _roll = call[2] + 360;
  _heading = call[3] + 360;

  _imuData.eulerAngles.yaw = adjustFrame(_yaw + yaw_OFFSET);
  _imuData.eulerAngles.pitch = adjustFrame(_pitch + pitch_OFFSET);
  _imuData.eulerAngles.roll = adjustFrame(_roll + roll_OFFSET);
  _imuData.heading = _heading;
}

IMUData IMU_RAZOR::get(){
  return _imuData;
}

float IMU_RAZOR::adjustFrame(float angle){
  if (angle > 180) angle = angle - 360;
  if (angle < -180) angle = angle + 360;
  return angle;
}

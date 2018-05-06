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
  _imuRazor.read();
}

IMUData IMU_RAZOR::get(){
  _imu.accelerometer = _imuRazor.getAccelerometer();
  _imu.magnetometer = _imuRazor.getMagnetometer();
  _imu.gyroscope = _imuRazor.getGyroscope();
  return _imu;
}

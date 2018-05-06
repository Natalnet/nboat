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
  _accelerometer.read();
  _magnetometer.read();
  _gyroscope.read();
}

IMUData IMU_RAZOR::get(){
  _imu.accelerometer = _accelerometer.get();
  _imu.magnetometer = _magnetometer.get();
  _imu.gyroscope = _gyroscope.get();
  return _imu;
}

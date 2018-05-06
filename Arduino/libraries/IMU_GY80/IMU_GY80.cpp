/*

  IMU_GY80.cpp - Library for getting curent heading from Compass model HMC6352.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/


#include "Arduino.h"
#include "IMU_GY80.h"
#include "Wire.h"

IMU_GY80::IMU_GY80(){
}

void IMU_GY80::read(){
  _accelerometer.read();
  _magnetometer.read();
  _gyroscope.read();
}

IMUData IMU_GY80::get(){
  _imu.accelerometer = _accelerometer.get();
  _imu.magnetometer = _magnetometer.get();
  _imu.gyroscope = _gyroscope.get();
  return _imu;
}

/*

  IMU_MPU6050.cpp - Library for getting curent heading from Compass model HMC6352.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/


#include "Arduino.h"
#include "IMU_MPU6050.h"
#include "Wire.h"

IMU_MPU6050::IMU_MPU6050(){
}

void IMU_MPU6050::read(){
  _accelAndGyro.read();
  _magnetometer.read();
}

IMUData IMU_MPU6050::get(){
  _imu.accelerometer = _accelAndGyro.getAccelerometer();
  _imu.magnetometer = _magnetometer.get();
  _imu.gyroscope = _accelAndGyro.getGyroscope();
  return _imu;
}





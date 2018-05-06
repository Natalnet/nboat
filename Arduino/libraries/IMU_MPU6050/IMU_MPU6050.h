/*

  IMU_MPU6050.h - Library for getting curent heading from Compass HMC6352.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#ifndef IMU_MPU6050_h
#define IMU_MPU6050_h

#include "Arduino.h"
#include "Mag_HMC5883L.h"
#include "IMUData.h"
#include "MPU6050.h"

class IMU_MPU6050
{
  public:
    IMU_MPU6050();
    void read();
    IMUData get();

  private:
    MPU6050 _accelAndGyro;
    Mag_HMC5883L _magnetometer;
    IMUData _imu;

};

#endif


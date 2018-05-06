/*

  MPU6050.h - Library for getting curent heading from Compass HMC6352.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#ifndef MPU6050_h
#define MPU6050_h

#include "Arduino.h"
#include "Mag_HMC5883L.h"
#include "IMUData.h"
#include "Wire.h"

class MPU6050
{
  public:
    MPU6050();
    void read();
    Pose getAccelerometer();
    Pose getGyroscope();

  private:
    Pose _accelerometer;
    Pose _gyroscope;
    int AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
    const int MPU = 0x68;

};

#endif


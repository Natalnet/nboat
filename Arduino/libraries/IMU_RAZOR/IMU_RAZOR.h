/*

  IMU_RAZOR.h - Library for getting curent heading from Compass HMC6352.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#ifndef IMU_RAZOR_h
#define IMU_RAZOR_h

#include "Arduino.h"
#include "Accel_ADXL345.h"
#include "Gyro_L3G4200D.h"
#include "Mag_HMC5883L.h"
#include "IMUData.h"
#include "Wire.h"

class IMU_RAZOR
{
  public:
    IMU_RAZOR();
    void read();
    IMUData get();

  private:
    Accel_ADXL345 _accelerometer;
    Gyro_L3G4200D _gyroscope;
    Mag_HMC5883L _magnetometer;
    IMUData _imu;

};

#endif


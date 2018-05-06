/*

  IMU_RAZOR.h - Library for getting curent heading from Compass HMC6352.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#ifndef IMU_RAZOR_h
#define IMU_RAZOR_h

#include "Arduino.h"
#include "Razor9DOF.h"
#include "IMUData.h"

class IMU_RAZOR
{
  public:
    IMU_RAZOR();
    void read();
    IMUData get();

  private:
    Razor9DOF _imuRazor;
    IMUData _imu;

};

#endif


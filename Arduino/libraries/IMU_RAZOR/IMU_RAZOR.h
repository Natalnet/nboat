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
    float IMU_RAZOR::adjustFrame(float angle);

  private:
    IMUData _imuData;
    float yaw_OFFSET = 105, pitch_OFFSET = 0, roll_OFFSET = -4;
    float _yaw, _pitch, _roll, _heading;

};

#endif


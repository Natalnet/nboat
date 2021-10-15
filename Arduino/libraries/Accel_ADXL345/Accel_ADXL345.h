/*

  Accel_ADXL345.h - Library for getting curent heading from Compass HMC6352.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#ifndef Accel_ADXL345_h
#define Accel_ADXL345_h

#include "Arduino.h"
#include "Pose.h"

#define Register_ID 0
#define Register_2D 0x2D
#define Register_X0 0x32
#define Register_X1 0x33
#define Register_Y0 0x34
#define Register_Y1 0x35
#define Register_Z0 0x36
#define Register_Z1 0x37

class Accel_ADXL345
{
  public:
    Accel_ADXL345();
    void read();
    Pose get();
  private:
    //calibration
    int ADXAddress, reading, val, _ctrl, X0, X1, X_out, Y0, Y1, Y_out, Z0, Z1, Z_out;
    float Xg, Yg, Zg;

    Pose _accelerometer;
};

#endif

/*

  Gyro_L3G4200D.h - Library for getting curent heading from Compass HMC6352.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#ifndef Gyro_L3G4200D_h
#define Gyro_L3G4200D_h

#include "Arduino.h"
#include "Pose.h"

#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24

class Gyro_L3G4200D
{
  public:
    Gyro_L3G4200D(int degreesPerSecond = 200);
    void read();
    Pose get();
  private:
    int readRegister(int deviceAddress, byte address);
    void writeRegister(int deviceAddress, byte address, byte val);
    int setupL3G4200D(int scale);
    void getGyroValues();
    int L3G4200D_Address, _x, _y, _z, _ctrl, _degreesPerSecond;
    byte xMSB, xLSB, yMSB, yLSB, zMSB, zLSB;
    Pose _gyroscope;
};

#endif

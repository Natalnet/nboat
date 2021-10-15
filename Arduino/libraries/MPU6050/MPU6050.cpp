/*

  MPU6050.cpp - Library for getting curent heading from Compass model HMC6352.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/


#include "Arduino.h"
#include "MPU6050.h"

MPU6050::MPU6050(){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0); 
  Wire.endTransmission(true);
}

void MPU6050::read(){

  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);

  Wire.requestFrom(MPU,14,true);  

  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  Tmp=Wire.read()<<8|Wire.read();
  GyX=Wire.read()<<8|Wire.read();
  GyY=Wire.read()<<8|Wire.read();
  GyZ=Wire.read()<<8|Wire.read();
  
  _accelerometer.x = AcX;
  _accelerometer.y = AcY;
  _accelerometer.z = AcZ;
  _gyroscope.x = GyX;
  _gyroscope.y = GyY;
  _gyroscope.z = GyZ;
}

Pose MPU6050::getAccelerometer(){
  return _accelerometer;
}

Pose MPU6050::getGyroscope(){
  return _gyroscope;
}



/*

  Accel_ADXL345.cpp - Library for getting curent heading from Compass model HMC6352.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/


#include "Arduino.h"
#include "Accel_ADXL345.h"
#include "Wire.h"

Accel_ADXL345::Accel_ADXL345(){
  ADXAddress = 0x53;
  reading = 0;
  val = 0;
  Wire.begin();
  _ctrl = 1;
}

void Accel_ADXL345::read(){

  if(_ctrl == 1) {
    Wire.beginTransmission(ADXAddress);
    Wire.write(Register_2D);
    Wire.write(8);                //measuring enable
    Wire.endTransmission();       // stop transmitting
    _ctrl = 0;
  }
 
  //--------------X
  Wire.beginTransmission(ADXAddress); // transmit to device
  Wire.write(Register_X0);
  Wire.write(Register_X1);
  Wire.endTransmission();
  Wire.requestFrom(ADXAddress,2); 
  if(Wire.available()<=2)   
  {
    X0 = Wire.read();
    X1 = Wire.read(); 
    X1=X1<<8;
    X_out=X0+X1;   
  }

  //------------------Y
  Wire.beginTransmission(ADXAddress); // transmit to device
  Wire.write(Register_Y0);
  Wire.write(Register_Y1);
  Wire.endTransmission();
  Wire.requestFrom(ADXAddress,2); 
  if(Wire.available()<=2)   
  {
    Y0 = Wire.read();
    Y1 = Wire.read(); 
    Y1=Y1<<8;
    Y_out=Y0+Y1;
  }
  //------------------Z
  Wire.beginTransmission(ADXAddress); // transmit to device
  Wire.write(Register_Z0);
  Wire.write(Register_Z1);
  Wire.endTransmission();
  Wire.requestFrom(ADXAddress,2); 
  if(Wire.available()<=2)   
  {
    Z0 = Wire.read();
    Z1 = Wire.read(); 
    Z1=Z1<<8;
    Z_out=Z0+Z1;
  }
  //
  Xg=X_out/256.0;
  Yg=Y_out/256.0;
  Zg=Z_out/256.0;

  _accelerometer.x = Xg;
  _accelerometer.y = Yg;
  _accelerometer.z = Zg;
}

Pose Accel_ADXL345::get(){
  return _accelerometer;
}

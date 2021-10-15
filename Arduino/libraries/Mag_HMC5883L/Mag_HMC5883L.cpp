/*

  Mag_HMC5883L.cpp - Library for getting curent heading from Compass model HMC6352.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/


#include "Arduino.h"
#include "Mag_HMC5883L.h"
#include "Wire.h"

Mag_HMC5883L::Mag_HMC5883L(float gridNorth){
  HMC5883LAddress = 0x1E;
  Wire.begin();
  _ctrl = 1;
}

void Mag_HMC5883L::read(){

  if(_ctrl == 1) {
    Wire.beginTransmission(HMC5883LAddress); //open communication with HMC5883
    Wire.write(0x02); //select mode register
    Wire.write(0x00); //continuous measurement mode
    Wire.endTransmission();
    _ctrl = 0;
  }
 
  //Tell the HMC5883L where to begin reading data
  Wire.beginTransmission(HMC5883LAddress);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission();
  
 //Read data from each axis, 2 registers per axis
  Wire.requestFrom(HMC5883LAddress, 6);
  if(6<=Wire.available()){
    _x = Wire.read()<<8; //X msb
    _x |= Wire.read(); //X lsb
    _z = Wire.read()<<8; //Z msb
    _z |= Wire.read(); //Z lsb
    _y = Wire.read()<<8; //Y msb
    _y |= Wire.read(); //Y lsb
  }

  _magnetometer.x = (float)_x;
  _magnetometer.y = (float)_y;
  _magnetometer.z = (float)_z;
}

Pose Mag_HMC5883L::get(){
  return _magnetometer;
}

float Mag_HMC5883L::getHeading(){
  return atan2(_x,_y)*180/PI;
}

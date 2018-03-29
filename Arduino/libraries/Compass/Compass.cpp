/*

  Compass.cpp - Library for getting curent heading from compass.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/


#include "Arduino.h"
#include "Compass.h"
#include "Wire.h"

Compass::Compass(float gridNorth){
  HMC6352Address = 0x42;
  slaveAddress = HMC6352Address >> 1;
  Wire.begin();
  sum = 0;
  _gridNorth = gridNorth;
  i = 0;
}

float Compass::readHeading(){
  for (int j = 1; j <= 10; j++){
    Wire.beginTransmission(slaveAddress);
    Wire.write("A");
    Wire.endTransmission();
    delay(10);
    Wire.requestFrom(slaveAddress, 2);
    i = 0;
    while(Wire.available() && i < 2)
    { 
      headingData[i] = Wire.read();
      i++;
    }
    headingValue = headingData[0]*256 + headingData[1];
    heading = headingValue/10;
   //  heading = -heading;
    heading = heading - _gridNorth;
    
    if (heading > 180) heading = heading - 360;
    if (heading < -180) heading = heading + 360;
    
    sum += heading;
  }

 //  delay(100);
  return sum/10;
}

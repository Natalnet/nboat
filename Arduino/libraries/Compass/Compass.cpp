#include "Arduino.h"
#include "Compass.h"
#include "Wire.h"

Compass::Compass(float norte_quadr_buss){
  HMC6352Address = 0x42;
  slaveAddress = HMC6352Address >> 1;
  Wire.begin();
  soma = 0;
  _norte_quadr_buss = norte_quadr_buss;
}

float Compass::get_value(){
  for (int j = 1; j <= 10; j++){
  Wire.beginTransmission(slaveAddress);
  Wire.write("A");
  Wire.endTransmission();
  delay(10);
  Wire.requestFrom(slaveAddress, 2);
  int i = 0;
  while(Wire.available() && i < 2)
  { 
    headingData[i] = Wire.read();
    i++;
  }
  headingValue = headingData[0]*256 + headingData[1];
  heading = headingValue/10;
 //  heading = -heading;
  heading = heading - _norte_quadr_buss;
  
  if (heading > 180) heading = heading - 360;
  if (heading < -180) heading = heading + 360;
  
  soma += heading;
  }

 //  delay(100);
  return soma/10;
}

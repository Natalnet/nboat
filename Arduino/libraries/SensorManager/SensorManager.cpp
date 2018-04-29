/*

  SensorManager.cpp - Library for getting curent heading from Compass model HMC6352.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/


#include "Arduino.h"
#include "SensorManager.h"

SensorManager::SensorManager(){
  
}

//TODO
bool SensorManager::checkSensors(){
}

void SensorManager::read(){
  gps1.read();
  compass1.read();
  wind.read();
  magnetometer1.read();
}

GPSData SensorManager::getGPS(){
  return gps1.get();
}

float SensorManager::getCompass(){
  return compass1.getHeading();
}

WindData SensorManager::getWind(){
  return wind.get();
}

//TODO
IMUData SensorManager::getIMU(){
  //return imu1.get();
}

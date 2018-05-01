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
  imu1.read();
}

void SensorManager::readImu(){
  imu1.read();
}

GPSData SensorManager::getGPS(){
  return gps1.get();
}

Pose SensorManager::getMagnetometer(){
  return magnetometer1.get();
}

float SensorManager::getCompass(){
  return compass1.getHeading();
}

WindData SensorManager::getWind(){
  return wind.get();
}

IMUData SensorManager::getIMU(){
  return imu1.get();
}

void SensorManager::logSensorData(){
  dataFile = SD.open("testecom.txt", FILE_WRITE);
  if (dataFile) {
    /*dataFile.print(currentLocation.latitude, 6);
    dataFile.print(" ");
    dataFile.print(currentLocation.longitude, 6);
    dataFile.print(" ");
    dataFile.print(startLocation.latitude, 6);
    dataFile.print(" ");
    dataFile.print(startLocation.longitude, 6);
    dataFile.print(" ");
    dataFile.print(nextLocation.latitude, 6);
    dataFile.print(" ");
    dataFile.print(nextLocation.longitude, 6);
    dataFile.print(" ");
    dataFile.print(heading, 2);
    dataFile.print(" ");
    dataFile.print(sp);
    dataFile.print(" ");
    dataFile.print(biruta, 2);
    dataFile.print(" ");
    dataFile.println(distanciaInicial);
    dataFile.print(" ");
    dataFile.print(distanciaAoDestino);*/
    dataFile.close();
  }
}

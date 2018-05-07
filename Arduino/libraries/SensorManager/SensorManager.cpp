/*

  SensorManager.cpp - Library for getting curent heading from Compass model HMC6352.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/


#include "Arduino.h"
#include "SensorManager.h"

SensorManager::SensorManager(){
  SD.begin(48);
}

//TODO
bool SensorManager::checkSensors(){
}

void SensorManager::read(){
  gps1.read();
  compass1.read();
  wind.read();
  //magnetometer1.read();
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

float SensorManager::getSailAngle(){
  return actDrivers->getSailAngle();
}

float SensorManager::getRudderAngle(){
  return actDrivers->getRudderAngle();
}

//posição (lat, lon), velocidade do vento (direção, speed), posição dos atuadores (leme, vela), velocidade (speed) e orientação do gps (course), orientação da bussola (heading), informações do IMU (R, P, Y).
void SensorManager::logState(){
  if (gps1.get().date != "" && gpsDateCtrl == 0) {
    _experimentName = String(gps1.get().date+".txt");
    gpsDateCtrl = 1;
  }

  if (gpsDateCtrl == 1){
    dataFile = SD.open(_experimentName, FILE_WRITE);
    if (dataFile) {
      dataFile.print(gps1.get().location.latitude, 6);
      dataFile.print(" ");
      dataFile.print(gps1.get().location.longitude, 6);
      dataFile.print(" ");
      dataFile.print(wind.get().direction, 2);
      dataFile.print(" ");
      dataFile.print(wind.get().speed, 2);
      dataFile.print(" ");
      dataFile.print(actDrivers->getRudderAngle(), 2);
      dataFile.print(" ");
      dataFile.print(actDrivers->getSailAngle(), 2);
      dataFile.print(" ");
      dataFile.print(gps1.get().course, 2);
      dataFile.print(" ");
      dataFile.print(gps1.get().speed, 2);
      dataFile.print(" ");
      dataFile.print(imu1.get().accelerometer.x, 2);
      dataFile.print(" ");
      dataFile.print(imu1.get().accelerometer.y, 2);
      dataFile.print(" ");
      dataFile.print(imu1.get().accelerometer.z, 2);
      dataFile.print(" ");
      dataFile.print(imu1.get().gyroscope.x, 2);
      dataFile.print(" ");
      dataFile.print(imu1.get().gyroscope.y, 2);
      dataFile.print(" ");
      dataFile.print(imu1.get().gyroscope.z, 2);
      dataFile.print(" ");
      dataFile.print(imu1.get().magnetometer.x, 2);
      dataFile.print(" ");
      dataFile.print(imu1.get().magnetometer.y, 2);
      dataFile.print(" ");
      dataFile.print(imu1.get().magnetometer.z, 2);
      dataFile.print(" ");
      dataFile.println(compass1.getHeading(), 2);
      
      dataFile.close();
    }
  }
}

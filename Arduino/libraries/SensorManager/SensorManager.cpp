/*

  SensorManager.cpp - Library for getting curent heading from Compass model HMC6352.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/


#include "Arduino.h"
#include "SensorManager.h"

SensorManager::SensorManager(){
  SD.begin(48);
  //Serial.print("TESTE");
  imu2 = new IMU_GY80();  
}

//TODO
bool SensorManager::checkSensors(){
}

void SensorManager::read(){
  gps1.read();
  //compass1.read();
  //wind.read();
  //magnetometer1.read();
  //imu1.read();
  imu2->read();
}

void SensorManager::readImu(){
//  imu1.read();
  imu2->read();
}

GPSData SensorManager::getGPS(){
  return gps1.get();
}

Pose SensorManager::getMagnetometer(){
//  return magnetometer1.get();
}

float SensorManager::getCompass(){
 // return compass1.getHeading();
}

WindData SensorManager::getWind(){
  return wind.get();
}

IMUData SensorManager::getIMU(){
//  return imu1.get();
  return  imu2->get();
}

void SensorManager::setSailAngle(float sailAngle){
  _sailAngle = sailAngle;
}

void SensorManager::setRudderAngle(float rudderAngle){
  _rudderAngle = rudderAngle;
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
      dataFile.print(wind.get ().direction, 2);
      dataFile.print(" ");
      dataFile.print(wind.get().speed, 2);
      dataFile.print(" ");
      dataFile.print(_rudderAngle, 2);
      dataFile.print(" ");
      dataFile.print(_sailAngle, 2);
      dataFile.print(" ");
      dataFile.print(gps1.get().course, 2);
      dataFile.print(" ");
      dataFile.print(gps1.get().speed, 2); 
      dataFile.print(" ");

      
      dataFile.print(imu2->get().eulerAngles.yaw, 2);
      dataFile.print(" ");
      dataFile.print(imu2->get().eulerAngles.pitch, 2);
      dataFile.print(" ");
      dataFile.print(imu2->get().eulerAngles.roll, 2);
      dataFile.print(" ");
      dataFile.println(imu2->get().heading, 2);

/*
      dataFile.print(imu1.get().eulerAngles.yaw, 2);
      dataFile.print(" ");
      dataFile.print(imu1.get().eulerAngles.pitch, 2);
      dataFile.print(" ");
      dataFile.print(imu1.get().eulerAngles.roll, 2);
      dataFile.print(" ");
      dataFile.println(imu1.get().heading, 2);
  */    
      dataFile.close();
    }
  }
}

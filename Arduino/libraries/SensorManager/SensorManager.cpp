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
  wind.read();
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

void SensorManager::setWindSpeed(float windSpeed){
  _windData.speed = windSpeed;
}

//posição (lat, lon), velocidade do vento (direção, speed), posição dos atuadores (leme, vela), velocidade (speed) e orientação do gps (course), orientação da bussola (heading), informações do IMU (R, P, Y).
void SensorManager::logState(){

  if (gps1.get().date != "" && gpsDateCtrl == 0) {
    _experimentName = String(gps1.get().date+".txt");
    gpsDateCtrl = 1;

    dataFile = SD.open(_experimentName, FILE_WRITE);

    //first line of log file
    if (dataFile) {
      dataFile.print("TimeStamp");        dataFile.print(",");
      dataFile.print("Latitude");         dataFile.print(",");
      dataFile.print("Longitude");        dataFile.print(",");
      dataFile.print("Wind Direction");   dataFile.print(",");
      dataFile.print("Wind Speed");       dataFile.print(",");
      dataFile.print("Rudder Angle");     dataFile.print(",");
      dataFile.print("Sail Angle");       dataFile.print(",");
      dataFile.print("GPS Course");       dataFile.print(",");
      dataFile.print("GPS Speed");        dataFile.print(",");
      dataFile.print("Yaw");              dataFile.print(",");
      dataFile.print("Pitch");            dataFile.print(",");
      dataFile.print("Roll");             dataFile.print(",");
      dataFile.println("Magnetometer Heading");
    }
    dataFile.close();
  }

  if (gpsDateCtrl == 1){
    dataFile = SD.open(_experimentName, FILE_WRITE);
    if (dataFile) {

      dataFile.print(timeStamp, 2);                         dataFile.print(",");
      dataFile.print(gps1.get().location.latitude, 6);      dataFile.print(",");
      dataFile.print(gps1.get().location.longitude, 6);     dataFile.print(",");
      dataFile.print(wind.get().direction, 2);              dataFile.print(",");
      dataFile.print(wind.get().speed, 2);                  dataFile.print(",");
      dataFile.print(_rudderAngle, 2);                      dataFile.print(",");
      dataFile.print(_sailAngle, 2);                        dataFile.print(",");
      dataFile.print(gps1.get().course, 2);                 dataFile.print(",");
      dataFile.print(gps1.get().speed, 2);                  dataFile.print(",");
      dataFile.print(imu2->get().eulerAngles.yaw, 2);       dataFile.print(",");
      dataFile.print(imu2->get().eulerAngles.pitch, 2);     dataFile.print(",");
      dataFile.print(imu2->get().eulerAngles.roll, 2);      dataFile.print(",");
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
      timeStamp += 0.2;
    }
  }
}

void SensorManager::printState()
{
	Serial.print(gps1.get().location.latitude, 6);
	Serial.print(" ");
	Serial.print(gps1.get().location.longitude, 6);
	Serial.print(" ");
	Serial.print(wind.get ().direction, 2);
	Serial.print(" ");
	Serial.print(wind.get().speed, 2);
	Serial.print(" ");
	Serial.print(_rudderAngle, 2);
	Serial.print(" ");
	Serial.print(_sailAngle, 2);
	Serial.print(" ");
	Serial.print(gps1.get().course, 2);
	Serial.print(" ");
	Serial.print(gps1.get().speed, 2); 
	Serial.print(" ");
	Serial.print(imu2->get().eulerAngles.yaw, 2);
	Serial.print(" ");
	Serial.print(imu2->get().eulerAngles.pitch, 2);
	Serial.print(" ");
	Serial.print(imu2->get().eulerAngles.roll, 2);
	Serial.print(" ");
	Serial.println(imu2->get().heading, 2); 
}

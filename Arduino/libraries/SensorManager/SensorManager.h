/*

  SensorManager.h - Library for getting curent heading from Compass HMC6352.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#ifndef SensorManager_h
#define SensorManager_h

#include "Arduino.h"
#include <SD.h>
#include <SPI.h>

#include "wqboatActuatorDrivers.h"
#include "Pose.h"
//#include "IMU_RAZOR.h"
#include "GPSData.h"
#include "IMUData.h"
#include "WindData.h"



class SensorManager
{
  public:
    SensorManager();    

    void logState();
    void sendStateToBase();

    float getCompass();
    WindData getWind();
    Pose getMagnetometer();
    void setThrusterPower(float ThrusterPower);
    void setRudderAngle(float rudderAngle);
    void setWindSpeed(float windSpeed);
    void SensorManager::printState();
    void SensorManager::setTack(bool isTack);
    void SensorManager::setWaypointId(int waypointId);
    void SensorManager::setAutoPilot(int autoPilot);
    void SensorManager::setGPSData(float lat, float lon, float course, float speed, float altitude, String date);
    void SensorManager::setIMUData(float roll, float pitch, float yaw, float accel_x, float accel_y, float accel_z, float gyro_x, float gyro_y, float gyro_z, float mag_x, float mag_y, float mag_z, float temperature, float pressure, float altitude);
    void SensorManager::setWindData(float windDir);
    void SensorManager::readFromSerial();
    GPSData SensorManager::getGPS();
    IMUData SensorManager::getIMU();

  private:
    
    wqboatActuatorDrivers *actDrivers;
    float call[18];

    float _batCharge; //TODO
    float _rudderAngle, _thrusterPower;

    File dataFile;

    int gpsDateCtrl = 0;

    String _experimentName;
    float timeStamp = 0;
    bool _isTack;
    int _waypointId;
    float _startTime, _endTime;
    int _autoPilot = 1;
    String _date;

    WindData _windData;
    GPSData _GPSData;
    IMUData _IMUData;
    
};

#endif

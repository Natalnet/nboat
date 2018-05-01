/*

  SensorManager.h - Library for getting curent heading from Compass HMC6352.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#ifndef SensorManager_h
#define SensorManager_h

#include "Arduino.h"
#include <SD.h>

//include all sensors lib available
#include "Mag_HMC5883L.h"
#include "Compass_HMC6352.h"
#include "GPS_EM506.h"
#include "WindSensor.h"
#include "IMU_GY80.h"

#include "GPSData.h"
#include "IMUData.h"
#include "WindData.h"



class SensorManager
{
  public:
    SensorManager();

    void read();
    void readImu()
    bool checkSensors();

    GPSData getGPS();
    IMUData getIMU();
    float getCompass();
    WindData getWind();
    Pose getMagnetometer();
    void logSensorData();
  private:
    Mag_HMC5883L magnetometer1;

    Compass_HMC6352 compass1;

    GPS_EM506 gps1;

    WindSensor wind;

    IMU_GY80 imu1;

    WindData _windData;
    GPSData _GPSData;
    IMUData _IMUData;

    float _batCharge; //TODO

    float _rudderAngle, _sailAngle;

    File dataFile;
    
};

#endif

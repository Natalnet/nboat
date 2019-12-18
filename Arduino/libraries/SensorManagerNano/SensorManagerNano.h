/*

  SensorManagerNano.h - Library for getting curent heading from Compass HMC6352.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#ifndef SensorManagerNano_h
#define SensorManagerNano_h

#include "Arduino.h"
#include <SD.h>
#include <SPI.h>

//include all sensors lib available
//#include "Mag_HMC5883L.h"
//#include "Compass_HMC6352.h"
#include "GPS_EM506.h"
#include "WindSensor.h"
#include "IMU_GY80.h"
#include "Pose.h"
//#include "IMU_RAZOR.h"
#include "GPSData.h"
#include "IMUData.h"
#include "WindData.h"



class SensorManagerNano
{
  public:
    SensorManagerNano();

    void read();
    void readImu();
    bool checkSensors();

    void logState();
    void sendStateToBase();

    GPSData getGPS();
    IMUData getIMU();
    float getCompass();
    WindData getWind();
    Pose getMagnetometer();
    void setThrusterPower(float ThrusterPower);
    void setRudderAngle(float rudderAngle);
    void setWindSpeed(float windSpeed);
    void SensorManagerNano::printState();
    void SensorManagerNano::sendStateToMaster();

    WindData _windData;
    GPSData _GPSData;
    IMUData _IMUData;
  private:
    
    float call[7];
    
//    Mag_HMC5883L magnetometer1;

//    Compass_HMC6352 compass1;

    GPS_EM506 gps1;

    WindSensor wind;

    //IMU_RAZOR imu1;
    IMU_GY80 *imu1;

    float _batCharge; //TODO

    File dataFile;

    int gpsDateCtrl = 0;

    String _experimentName;
    float timeStamp = 0;
    float _startTime, _endTime;

    float _rudderAngle = 0;
    float _thrusterPower = 0;
    int _autoPilot = 1;
    float _waypointId = 0;
};

#endif

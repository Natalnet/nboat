#include "GPS_EM506.h"
#include "WindSensor.h"
#include "Mag_HMC5883L.h"
#include "Compass_HMC6352.h"
#include "SensorManager.h"
#include "SailboatControl.h"
#include "IMU_GY80.h"

//SensorManager sensors;
//IMU_GY80 imu;
//GPS_EM506 gps;
SensorManager *sensors;
//GPSData gpsData;
//Location loc;

void setup() {
  Serial.begin(9600);
  sensors = new SensorManager();
}

void loop() {
  //imu.read();
  //float test = imu.get().accelerometer.x;
  //Serial.println();
  //Serial.println(sensors.getGPS().location.latitude);
  float time1 = millis();
  //gps.read();
  sensors->read();
  Serial.println(millis()-time1);
  Serial.print(sensors->getGPS().location.latitude,  6);
  Serial.print("---------------- ");
  Serial.print(sensors->getGPS().location.longitude, 6);
  Serial.print("---------------- ");
  Serial.print(sensors->getGPS().course, 2);
  Serial.print("---------------- ");
  Serial.print(sensors->getGPS().speed, 2);
  Serial.print("---------------- ");
  Serial.print(sensors->getGPS().dateFull);
  Serial.print("---------------- ");
  //Serial.print(comp.readHeading());
}




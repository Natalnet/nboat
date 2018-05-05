#include "GPS_EM506.h"
#include "WindSensor.h"
#include "Mag_HMC5883L.h"
#include "Compass_HMC6352.h"
#include "SensorManager.h"
#include "SailboatControl.h"
#include "IMU_GY80.h"
//#include "Compass.h"

SensorManager sensors;
IMU_GY80 imu;
GPS_EM506 gps;
GPSData gpsData;
Location loc;

void setup() {
  Serial.begin(9600);
}

void loop() {
  //imu.read();
  //float test = imu.get().accelerometer.x;
  //Serial.println();
  //Serial.println(sensors.getGPS().location.latitude);
  float time1 = millis();
  gps.read();
  Serial.println(millis()-time1);
  Serial.print(gps.get().location.latitude,  6);
  Serial.print("---------------- ");
  Serial.print(gps.get().location.longitude, 6);
  Serial.print("---------------- ");
  Serial.print(gps.get().course, 2);
  Serial.print("---------------- ");
  //Serial.print(comp.readHeading());
}




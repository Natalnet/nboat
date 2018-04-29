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

void setup() {
  Serial.begin(9600);
}

void loop() {
  imu.read();
  float test = imu.get().accelerometer.x;
  Serial.println();
  //Serial.println(sensors.getGPS().location.latitude);
  /*loc = gps.readPosition();
  Serial.print(loc.latitude,  6);
  Serial.print(", ");
  Serial.print(loc.longitude, 6);
  Serial.print("---------------- ");
  Serial.print(comp.readHeading());
  Serial.println();*/
}




#include <SD.h>
#include <SPI.h>

//include all sensors lib available
//#include "Mag_HMC5883L.h"
//#include "Compass_HMC6352.h"
#include "GPS_EM506.h"
#include "WindSensor.h"
#include "IMU_GY80Nano.h"
//#include "IMU_RAZOR.h"


//INSTATIATING LIBS
GPS_EM506 gps;
IMU_GY80Nano *imu;
WindSensor wind;


void setup() {
  imu = new IMU_GY80Nano();
  Serial.begin(57600);
}

void loop() {
  readSensors();
  if(Serial.available() > 0){
    if(Serial.read() == 'f'){
      sendStateToMaster();
    }
  }
}

void readSensors(){
  gps.read();
  wind.read();
  imu->read();
}

void sendStateToMaster()
{
  Serial.println(gps.get().location.latitude, 6);
  Serial.println(gps.get().location.longitude, 6);
  Serial.println(gps.get().course, 2);
  Serial.println(gps.get().speed, 2);
  Serial.println(gps.get().altitude, 2);
  
  Serial.println(imu->get().accel_x, 2);
  Serial.println(imu->get().accel_y, 2);
  Serial.println(imu->get().accel_z, 2);
  Serial.println(imu->get().gyro_x, 2);
  Serial.println(imu->get().gyro_y, 2);
  Serial.println(imu->get().gyro_z, 2);
  Serial.println(imu->get().mag_x, 2);
  Serial.println(imu->get().mag_y, 2);
  Serial.println(imu->get().mag_z, 2);
  Serial.println(imu->get().temperature, 2);
  Serial.println(imu->get().pressure, 2);
  Serial.println(imu->get().altitude, 2);
  
  Serial.println(wind.getDirectionSigned(), 2);
  
  Serial.println(gps.get().date);
}

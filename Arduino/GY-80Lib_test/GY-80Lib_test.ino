#include "IMU_GY80.h"

IMU_GY80 *imu;
float time1, time2;

void setup() {
  imu = new IMU_GY80();
  Serial.begin(9600);
}

void loop() {
  time1 = millis();
  imu->read();
  time2 = millis();
  //Serial.println(time2-time1);
  Serial.print(imu->get().eulerAngles.yaw); Serial.print(" ");
  Serial.print(imu->get().eulerAngles.roll); Serial.print(" "); 
  Serial.print(imu->get().eulerAngles.pitch); Serial.print(" ");
  Serial.println(imu->get().heading);
}

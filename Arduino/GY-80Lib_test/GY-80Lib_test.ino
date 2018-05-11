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
  Serial.println(imu->get().eulerAngles.yaw);
  Serial.println(imu->get().);
  Serial.println(imu->get().eulerAngles.yaw);
}

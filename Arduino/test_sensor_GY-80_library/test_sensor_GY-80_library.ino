#include "IMU_GY80.h"

IMU_GY80 *imu;

void setup() {
  imu = new IMU_GY80();
  Serial.begin(9600);
}

void loop() {
  imu->read();
  Serial.print(imu->get().eulerAngles.yaw); Serial.print(" ");
  Serial.print(imu->get().eulerAngles.roll); Serial.print(" "); 
  Serial.print(imu->get().eulerAngles.pitch); Serial.print(" "); 
//  Serial.print(imu->get().accel_x); Serial.print(" ");
//  Serial.print(imu->get().accel_y); Serial.print(" ");
//  Serial.print(imu->get().accel_z); Serial.print(" ");
//  Serial.print(imu->get().gyro_x); Serial.print(" ");
//  Serial.print(imu->get().gyro_y); Serial.print(" ");
//  Serial.print(imu->get().gyro_z); Serial.print(" ");
//  Serial.print(imu->get().mag_x); Serial.print(" ");
//  Serial.print(imu->get().mag_y); Serial.print(" ");
//  Serial.print(imu->get().mag_z); Serial.print(" ");

  Serial.print(imu->get().temperature); Serial.print(" ");
  Serial.println(imu->get().heading);
}

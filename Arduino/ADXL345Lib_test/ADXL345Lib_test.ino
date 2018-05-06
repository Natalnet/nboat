#include "Accel_ADXL345.h"
#include "IMU_GY80.h"

//Accel_ADXL345 accel;
IMU_GY80 imu;

void setup() {
  Serial.begin(9600);
}

void loop() {
  //accel.read();
  imu.read();
  Serial.println("----- Getting Accelerometer -----");
  Serial.print(imu.get().accelerometer.x);
  Serial.print("; ");
  Serial.print(imu.get().accelerometer.y);
  Serial.print("; ");
  Serial.println(imu.get().accelerometer.z);
  Serial.println("----- Getting Gyroscope -----");
  Serial.print(imu.get().gyroscope.x);
  Serial.print("; ");
  Serial.print(imu.get().gyroscope.y);
  Serial.print("; ");
  Serial.println(imu.get().gyroscope.z);  
  Serial.println("----- Getting Magnetometer -----");
  Serial.print(imu.get().magnetometer.x);
  Serial.print("; ");
  Serial.print(imu.get().magnetometer.y);
  Serial.print("; ");
  Serial.println(imu.get().magnetometer.z);  
}

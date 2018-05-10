#include "IMU_RAZOR.h"

IMU_RAZOR imu;

void setup() {
  Serial.begin(9600);

}

void loop() {
  imu.read();
  Serial.print(imu.get().eulerAngles.yaw); Serial.print(" ");
  Serial.print(imu.get().eulerAngles.roll); Serial.print(" "); 
  Serial.print(imu.get().eulerAngles.pitch); Serial.print(" ");
  Serial.println(imu.get().heading);
}


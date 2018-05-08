#include "IMU_RAZOR.h"

IMU_RAZOR imu;

void setup() {
  Serial.begin(9600);

}

void loop() {
  imu.read();
  Serial.println(imu.get().heading);
}


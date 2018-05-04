#include "SensorManager.h"

SensorManager test;

void setup() {
  Serial.begin(9600);

}

void loop() {
  float time1, time2;
  time1 = millis();
  test.read();
  time2 = millis();
  //Serial.print("Time: ");
  //Serial.println(time2-time1);
  
  Serial.print(test.getGPS().location.latitude, 6);
  Serial.print(" ");
  Serial.print(test.getGPS().location.longitude, 6);
  Serial.print(" ");
  Serial.print(test.getWind().direction, 2);
  Serial.print(" ");
  Serial.print(test.getWind().speed, 2);
  Serial.print(" ");
  Serial.print(test.getGPS().course, 2);
  Serial.print(" ");
  Serial.print(test.getGPS().speed, 2);
  Serial.print(" ");
  Serial.print(test.getIMU().accelerometer.x, 2);
  Serial.print(" ");
  Serial.print(test.getIMU().accelerometer.y, 2);
  Serial.print(" ");
  Serial.print(test.getIMU().accelerometer.z, 2);
  Serial.print(" ");
  Serial.print(test.getIMU().gyroscope.x, 2);
  Serial.print(" ");
  Serial.print(test.getIMU().gyroscope.y, 2);
  Serial.print(" ");
  Serial.print(test.getIMU().gyroscope.z, 2);
  Serial.print(" ");
  Serial.print(test.getIMU().magnetometer.x, 2);
  Serial.print(" ");
  Serial.print(test.getIMU().magnetometer.y, 2);
  Serial.print(" ");
  Serial.print(test.getIMU().magnetometer.z, 2);
  Serial.print(" ");
  Serial.print(test.getCompass(), 2);
  Serial.println(" ");
}



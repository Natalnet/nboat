#include "SensorManager.h"
 
SensorManager test;

//task scheduler
typedef struct t  {
    unsigned long tStart;
    unsigned long tTimeout;
};

//Tasks and their Schedules.
t t_func1 = {0, 200}; //Run every 100ms
t t_func2 = {0, 2000}; //Run every 2 seconds.

bool tCheck (struct t *t ) {
  if (millis() > t->tStart + t->tTimeout) return true;
}

void tRun (struct t *t) {
    t->tStart = millis();
}
 
void setup() {
  Serial.begin(9600);
}
 
void loop() {
  float time1, time2;
  time1 = millis();
  if (tCheck(&t_func1)) {
      test.read();
      tRun(&t_func1);
      time2 = millis();
      Serial.print("Time func 1: ");
      Serial.println(time2-time1);
  }
  
  if (tCheck(&t_func2)) {
      //print_data();
      tRun(&t_func2);
      time2 = millis();
      Serial.print("Time func 2: ");
      Serial.println(time2-time1);
  }
}

void print_data(){
  Serial.print(test.getGPS().location.latitude, 6);
  Serial.print(" ");
  Serial.print(test.getGPS().location.longitude, 6);
  Serial.print(" ");
  Serial.print(test.getWind().direction, 2);
  Serial.print(" ");
  Serial.print(test.getWind().speed, 2);
  Serial.print(" ");
  Serial.print(test.getSailAngle(), 2);
  Serial.print(" ");
  Serial.print(test.getRudderAngle(), 2);
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


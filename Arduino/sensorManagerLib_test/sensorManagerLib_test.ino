#include "SensorManager.h"
#include "SailboatMiniActuatorDrivers.h"
 
SensorManager *test;
float time1, time2;
SailboatMiniActuatorDrivers *driver;
//SailboatMiniActuatorDrivers driver1;

//task scheduler
typedef struct t  {
    unsigned long tStart;
    unsigned long tTimeout;
};

//Tasks and their Schedules.
t t_func1 = {0, 50}; //Run every 100ms
t t_func2 = {0, 2000}; //Run every 2 seconds.

bool tCheck (struct t *t ) {
  if (millis() > t->tStart + t->tTimeout){
    //Serial.print("IS TRUE? ");
    //Serial.println(millis() - t->tStart);
    return true;
  } else {
    return false;
  }
}

void tRun (struct t *t) {
    t->tStart = millis();
}
 
void setup() {
  Serial.begin(9600);
  test = new SensorManager();
  driver = new SailboatMiniActuatorDrivers();
  time1 = millis();
}
 
void loop() {
  test->read();
  driver->setRudderAngle(90);
  driver->setSailAngle(50);
  Serial.print("VALOR DO LEME:  ");
  Serial.println(driver->getRudderAngle());
  Serial.print("VALOR DO SERVO LEME:  ");
  Serial.println(driver->getRudderServo());
  Serial.print("VALOR DO SERVO VELA:  ");
  Serial.println(driver->getSailServo());
  test->setSailAngle(driver->getSailAngle());
  test->setRudderAngle(driver->getRudderAngle());
  if (tCheck(&t_func1)) {
    //print_data();
    test->sendState();
    Serial.println();
    //Serial.print(t_func1.tStart/1000);
    tRun(&t_func1);
  }
  //Serial.print("teste");
  //test.read();
  //time1 = millis();
  //test.logState();
  //time2 = millis();
  //Serial.println(time2-time1);
  //test.read();
  //print_data();
  /*if (tCheck(&t_func2)) {
      //print_data();
      tRun(&t_func2);
      time2 = millis();
      Serial.print("Time func 2: ");
      Serial.println(time2-time1);
  }*/
}

/*void print_data(){
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
  Serial.print(test.getIMU().eulerAngles.yaw, 2);
  Serial.print(" ");
  Serial.print(test.getIMU().eulerAngles.pitch, 2);
  Serial.print(" ");
  Serial.print(test.getIMU().eulerAngles.roll, 2);
  Serial.print(" ");
  Serial.println(test.getIMU().heading, 2);
}*/

/*void print_data(){
  Serial.print(test->getGPS().location.latitude, 6);
  Serial.print(" ");
  Serial.print(test->getGPS().location.longitude, 6);
  Serial.print(" ");
  Serial.print(test->getWind().direction, 2);
  Serial.print(" ");
  Serial.print(test->getWind().speed, 2);
  Serial.print(" ");
  Serial.print(test->getSailAngle(), 2);
  Serial.print(" ");
  Serial.print(test->getRudderAngle(), 2);
  Serial.print(" ");
  Serial.print(test->getGPS().course, 2);
  Serial.print(" ");
  Serial.print(test->getGPS().speed, 2);
  Serial.print(" ");
  Serial.print(test->getIMU().eulerAngles.yaw, 2);
  Serial.print(" ");
  Serial.print(test->getIMU().eulerAngles.pitch, 2);
  Serial.print(" ");
  Serial.print(test->getIMU().eulerAngles.roll, 2);
  Serial.print(" ");
  Serial.println(test->getIMU().heading, 2);
}*/

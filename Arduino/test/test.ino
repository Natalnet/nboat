#include "Location.h"
#include "ActuatorsDrivers.h"

Location loc1;
Location loc2;
ActuatorsDrivers boatAct;
float angle;

void setup() {
  Serial.begin(9600);

}

void loop() {
  
   for(int i = 0; i <= 150; i = i+10){
    boatAct.setThrusterPower(i);
    Serial.println(i);
    delay(1000);
  }
  
  for(int i = 140; i >= 0; i = i-10){
    boatAct.setThrusterPower(i);
    Serial.println(i);
    delay(1000);
  }
  // put your main code here, to run repeatedly:
  //loc.latitude = 10.0;
  //loc1.latitude = 5.0;
  //loc2.latitude = 7.0;
  //Serial.println(loc1.latitude);
  //Serial.println(loc2.latitude);
  /*boatAct.setRudderPositionBoat(0);
  delay(500);
  boatAct.setRudderPositionBoat(30);
  delay(500);
  boatAct.setRudderPositionBoat(60);
  delay(500);
  boatAct.setRudderPositionBoat(90);
  delay(500);
  boatAct.setRudderPositionBoat(60);
  delay(500);
  boatAct.setRudderPositionBoat(30);
  delay(500);
  boatAct.setRudderPositionBoat(0);
  delay(500);
  boatAct.setRudderPositionBoat(-30);
  delay(500);
  boatAct.setRudderPositionBoat(-60);
  delay(500);
  boatAct.setRudderPositionBoat(-90);
  delay(500);
  boatAct.setRudderPositionBoat(-60);
  delay(500);
  boatAct.setRudderPositionBoat(-30);
  delay(500);
  boatAct.setRudderPositionBoat(0);
  delay(500);*/
  //boatAct.setRudderPositionBoat(45);
  //boatAct.setThrusterPower(0);
  //delay(1000);
  //boatAct.setThrusterPower(0);
  //delay(1000);
  //boatAct.setThrusterPower(25);
  //delay(5000);
  //boatAct.setThrusterPower(50);
  //delay(2000);
  //boatAct.setThrusterPower(75);
  //delay(1000);
  //boatAct.setThrusterPower(100);
  //delay(1000);
  //Serial.println(map(0, 0, 100, 0, 50));
}



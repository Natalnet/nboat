#include "DualVNH5019MotorShield.h" //drive motor
DualVNH5019MotorShield md(2, 7, 6, A0, 2, 7, 12, A1);

//pot vela A3
//þot leme A2. min = 435; max = 647;

int sensorPin = A3;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  md.init();
  Serial.begin(9600);
}
 
void loop() {
  /*for(int i = 0; i < 200; i = i + 10){
    md.setM1Speed(i);
    delay(500);
  }*/

//  sensorValue = analogRead(sensorPin);
//  Serial.println(sensorValue);
  md.setM1Speed(-400); //-400 <-> +400
  delay(4000);
  md.setM1Speed(0); //-400 <-> +400
  delay(500);
  md.setM1Speed(400); //-400 <-> +400
  delay(4000);
  md.setM1Speed(0); //-400 <-> +400
  delay(500);
  md.setM1Speed(0);
}

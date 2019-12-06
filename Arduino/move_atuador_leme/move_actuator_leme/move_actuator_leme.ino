#include "DualVNH5019MotorShield.h" //drive motor
DualVNH5019MotorShield md;

void setup() {
  md.init();
  Serial.begin(9600);

}

void loop() {
  md.setM1Speed(400);
  int pot_r = analogRead(A3);
  Serial.println(pot_r);
  //delay(4000);
  //md.setM1Speed(0);
  //delay(500);
  //md.setM1Speed(400);
  //delay(4000);
  //md.setM1Speed(0);
  //delay(500);
}

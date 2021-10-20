#include "DualVNH5019MotorShield.h"

//DualVNH5019MotorShield md(2, 7, 6, A0, 2, 7, 12, A1);
DualVNH5019MotorShield md;
int sensorPin = A3;
int sensorValue = 0;
int delay_motor = 2;

void stopIfFault()
{
  if (md.getM1Fault())
  {
    Serial.println("M1 fault");
    while(1);
  }
  if (md.getM2Fault())
  {
    Serial.println("M2 fault");
    while(1);
  } 
}

void setup()
{
  Serial.begin(9600);
  Serial.println("Dual VNH5019 Motor Shield");
  md.init();
}

void loop()
{
  for (int i = 0; i <= 400; i++)
  {
    md.setM2Speed(i);
    stopIfFault();
    sensorValue = analogRead(sensorPin);
    Serial.println(sensorValue);    
    delay(delay_motor);
  }
  
  for (int i = 400; i >= -400; i--)
  {
    md.setM2Speed(i);
    stopIfFault();
    sensorValue = analogRead(sensorPin);
    Serial.println(sensorValue);    
    delay(delay_motor);
  }
  
  for (int i = -400; i <= 0; i++)
  {
    md.setM2Speed(i);
    stopIfFault();
    sensorValue = analogRead(sensorPin);
    Serial.println(sensorValue);    
    delay(delay_motor);
  }
}

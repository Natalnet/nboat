/*

  ActuatorsDrivers.h - Library for the low level commands to put the actuators in a desired position.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/


#include "Arduino.h"
#include "ActuatorsDrivers.h"

ActuatorsDrivers::ActuatorsDrivers(){
  DualVNH5019MotorShield md(2, 7, 6, A0, 2, 7, 12, A1);  //temporary solution for the initialization of md
  _md = md;
  _md.init();
  _sailAngleMaxValue = 90;
  sailLowerLimit = 980; //0 degrees
  sailUpperLimit = 350; //90 degrees
}

// using a potentiometer as sensor
void ActuatorsDrivers::setSailPosition(float sailAngle, int analogAtuador){

  sensorReading = analogRead(analogAtuador);

  //convert from sail angle (0º->90º) to driver sensor (potentiometer) value (digital)
  desiredPosition = sailLowerLimit + (sailUpperLimit - sailLowerLimit) * (sailAngle/_sailAngleMaxValue);

  sensorError = desiredPosition - sensorReading;

  if(sensorError > 20){
    _md.setM1Speed(-200);
    //Serial.println("CLOSING SAIL!!");
  } else if(sensorError < -20){
    _md.setM1Speed(200);
    //Serial.println("OPENING SAIL!!");
  } else if ((sensorError >= 0 && sensorError <= 30) || (sensorError <= 0 && sensorError >= -30)){
    _md.setM1Speed(0);
    //Serial.println("SAIL STOPED!!");
  } else {
    _md.setM1Speed(0);
    //Serial.println("SAIL STOPED!!");
  }
  delay(200); //TODO this means that ONLY this function cant be called for at leasts 200 ms (actuator's settling time). find a better way to do this so the whole program dosent stop in this line.
}

//TODO
//void ActuatorsDrivers::setRudderPosition(){}

/*int saturador_atuador_cor(float sensor) {
  float id = (-sensor + 120)/30;
  int aux = (int)id;
  float decpart = id - aux;
  int idreturn = 1;
  if (decpart <= 0.5){
    idreturn = id;
  } else{
    idreturn = id + 1;
  }
  return idreturn;
}*/

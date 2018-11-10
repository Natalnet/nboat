/*

  WindSensor.cpp - Library for getting info from Wind sensors used in N-Boat project.
  Created by Davi H. dos Santos, March 28, 2018.
  BSD license, all text above must be included in any redistribution.

*/


#include "Arduino.h"
#include "WindSensor.h"

WindSensor::WindSensor(){
  starttime = millis();
  buttonState_ant = LOW;
  buttonState = LOW;
}

//read sensor
void WindSensor::read(){
  //_windData.speed = readSpeed();
  _windData.direction = readDirection();
}

//TODO extend this reading for some time. use interruption to count states LOW to HIGH
float WindSensor::readSpeed(int anemometerPin){
  buttonState_ant = buttonState;
  buttonState = digitalRead(anemometerPin);
  
  if (buttonState == HIGH && buttonState_ant == LOW) {
    endtime = millis();
    windSpeed = (((float) 1)/(endtime-starttime)*1000.0)*6.6667;
    starttime = millis();
  }
  
  return windSpeed;
}

float WindSensor::readDirection(int windvanePin){
  float sum = 0;
  int cont = 0;
  for(int i = 0; i < 10; i++){
    windvaneRead = analogRead(windvanePin);
    if(windvaneRead > 1000){
      windvaneRead = 0;
    } else {
      sum += windvaneRead;
      cont++;
    }
  }
  if(cont > 0){
    windvaneRead = sum/cont;
  } else {
    windvaneRead = windvaneReadAnt;
  }
  
  if(windvaneRead >= 750 && windvaneRead <= 800) {windDirection = 0;}
  if(windvaneRead >= 690 && windvaneRead <= 730) {windDirection = -22.5;}
  if(windvaneRead >= 865 && windvaneRead <= 885) {windDirection = -45;}
  if(windvaneRead >= 815 && windvaneRead <= 850) {windDirection = -67.5;}
  if(windvaneRead >= 925 && windvaneRead <= 945) {windDirection = -90;}
  if(windvaneRead >= 590 && windvaneRead <= 615) {windDirection = -112.5;}
  if(windvaneRead >= 605 && windvaneRead <= 625) {windDirection = -135;}
  if(windvaneRead >= 240 && windvaneRead <= 260) {windDirection = -157.5;}
  if(windvaneRead >= 265 && windvaneRead <= 285) {windDirection = 180;}
  if(windvaneRead >= 120 && windvaneRead <= 135) {windDirection = 157.5;}
  if(windvaneRead >= 155 && windvaneRead <= 175) {windDirection = 135;}
  if(windvaneRead >= 50 && windvaneRead <= 74) {windDirection = 112.5;}
  if(windvaneRead >= 65 && windvaneRead <= 85) {windDirection = 90;}
  //if(windvaneRead >= 75 && windvaneRead <= 83) {windDirection = 67.5;}
  if(windvaneRead >= 435 && windvaneRead <= 465) {windDirection = 45;}
  if(windvaneRead >= 400 && windvaneRead <= 420) {windDirection = 22.5;}
  _windDirectionSigned = windDirection;
  if(windDirection < 0) {windDirection = -windDirection;}

  windvaneReadAnt = windvaneRead;

  return windDirection;
}

//return values read from sensor
WindData WindSensor::get(){
  return _windData;
}

float WindSensor::getSpeed(){
  return _windData.speed;
}

float WindSensor::getDirection(){
  return _windData.direction;
}

float WindSensor::getDirectionSigned(){
  return _windDirectionSigned;
}

int WindSensor::getDirectionRaw(){
  return windvaneRead;
}

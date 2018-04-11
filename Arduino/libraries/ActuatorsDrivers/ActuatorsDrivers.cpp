/*

  ActuatorsDrivers.h - Library for the low level commands to put the actuators (sail and rudder) in a desired position.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/


#include "Arduino.h"
#include "ActuatorsDrivers.h"

ActuatorsDrivers::ActuatorsDrivers(){
  DualVNH5019MotorShield sailActuator(2, 7, 6, A0, 2, 7, 12, A1);  //temporary solution for the initialization of sailActuator
  _sailActuator = sailActuator;
  _sailActuator.init();
  _sailAngleMaxValue = 90;
  sailLowerLimit = 980; //0 degrees
  sailUpperLimit = 350; //90 degrees

   //TODO
  _rudderBoatLowerLimit = 50;
  _rudderBoatUpperLimit = 110;

  Serial.begin(9600);  //rx of arduino uno
  Serial1.begin(9600); //tx of arduino mega

  _rudderActuator.init();
  tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
}

// using a potentiometer as sensor
void ActuatorsDrivers::setSailPosition(float sailAngle, int sensorPin){

  sensorReading = analogRead(sensorPin);

  //convert from sail angle (0º->90º) to driver sensor (potentiometer) value (digital)
  desiredPosition = sailLowerLimit + (sailUpperLimit - sailLowerLimit) * (sailAngle/_sailAngleMaxValue);

  sensorError = desiredPosition - sensorReading;

  if(sensorError > 20){
    _sailActuator.setM1Speed(-200);
    //Serial.println("CLOSING SAIL!!");
  } else if(sensorError < -20){
    _sailActuator.setM1Speed(200);
    //Serial.println("OPENING SAIL!!");
  } else if ((sensorError >= 0 && sensorError <= 30) || (sensorError <= 0 && sensorError >= -30)){
    _sailActuator.setM1Speed(0);
    //Serial.println("SAIL STOPED!!");
  } else {
    _sailActuator.setM1Speed(0);
    //Serial.println("SAIL STOPED!!");
  }
  delay(200); //TODO this means that ONLY this function cant be called for at leasts 200 ms (actuator's settling time). find a better way to do this so the whole program dosent stop in this line.
}

//TODO how rudderAngle is going to get here???
void ActuatorsDrivers::setRudderPosition(float rudderAngle){
  int auxTemp = angleToColor(rudderAngle);
  //send this information to the appropriated driver
  Serial1.print(auxTemp);
}

void ActuatorsDrivers::setRudderPositionBoat(float rudderAngle, int rudderPin){
  //TODO measure rudder limits angle to valid angles
  //use the constrain(x, a, b)
  rudder.attach(rudderPin);
  rudder.write(map(rudderAngle, -90, 90, _rudderBoatLowerLimit, _rudderBoatUpperLimit));
}

void ActuatorsDrivers::setThrusterPower(float thrusterPower, int thrusterPin){
  thruster.attach(thrusterPin);
  //thruster.write(map(thrusterPower, 0, 100, 0, 179));
  thruster.write(thrusterPower);
}


//describe what this function should do!
int ActuatorsDrivers::angleToColor(float sensor) {
  //???????????????
  _id = (-sensor + 120)/30;

  //all this to round _id...
  _aux = (int)_id;
  _decpart = _id - _aux;
  int idreturn;
  if (_decpart <= 0.5){
    idreturn = _aux;
  } else{
    idreturn = _aux + 1;
  }
  return idreturn;
}

void ActuatorsDrivers::getRudderPosition(){
  //what does this variable does?
  //if (espera == 1) {
  if (Serial.available() > 0 ) {
   _command = Serial.read();
   if (_command == 'c') {
   moveRudder(4);
   }
   if (_command == '1') {
   moveRudder(1);
   }
   if (_command == '2') {
   moveRudder(2);
   }
   if (_command == '3') {
   moveRudder(3);
   }
   if (_command == '4') {
   moveRudder(4);
   }
   if (_command == '5') {
   moveRudder(5);
   }
   if (_command == '6') {
   moveRudder(6);
   }
   if (_command == '7') {
   moveRudder(7);
   }
   readCurrentRGB();
   delay(1000);
  }
  //}
}

void ActuatorsDrivers::moveRudder(int desiredColor) {
  //what is the purpose of this variable?
  //espera = 0;
  _rudderActuator.setM1Speed(0);
  readColor();
  while (_currentColor < desiredColor) {
    if (desiredColor - _currentColor <= 1) { 
    _rudderActuator.setM1Speed(200); } 
    else { 
    _rudderActuator.setM1Speed(400); }
    readColor();
    // Serial.println(_currentColor);
  }
  while (_currentColor > desiredColor) {
    if (_currentColor - desiredColor <= 1) { 
    _rudderActuator.setM1Speed(-200); } 
    else { 
    _rudderActuator.setM1Speed(-400); }
    readColor();
    // Serial.println(_currentColor);
  }
  //i think this is equivalent to Seria.flush(), so the buffer is cleared
  while (Serial.available() > 0 ) {
    char t = Serial.read();
  }
  //espera = 1;
  _rudderActuator.setM1Speed(0);
}

void ActuatorsDrivers::readColor() {

  tcs.setInterrupt(false);      // liga LED
  delay(60);  // leva 60ms para ler
  tcs.getRawData(&red, &green, &blue, &clear);
  tcs.setInterrupt(true);  // desliga LED

  lux = clear;
  r_red = lux / red;
  r_green = lux / green;
  r_blue = lux / blue;

  if(r_red >= 5.5){
    _currentColor = 1; //azul
    // Serial.println("azul");
  } else if((r_blue >= 4) && (r_green <= 3)){
    _currentColor = 2; //amarelo
    // Serial.println("amarelo");
  } else if((lux > 5500 && lux <= 7500) && (r_red >= 3.6 && r_red <= 4.4 ) && (r_green > 3)){
    _currentColor = 3; //roxo
    // Serial.println("roxo");
  } else if((lux <= 3500) && (r_red >= 2.5 && r_red < 3.5)){
    _currentColor = 4; //preto
    // Serial.println("preto");
  } else if((r_blue >= 4.2) && (r_green > 3 && r_green <= 4)){
    _currentColor = 5; //laranja
    // Serial.println("laranja");
  } else if((r_red > 3.5) && (r_green <= 2.8)){
    _currentColor = 6; //verde
    // Serial.println("verde");
  } else if(r_green >= 4){
    _currentColor = 7; //vermelho
    // Serial.println("vermelho");
  } else {
    // Serial.println("nao identificada");
  }
}

void ActuatorsDrivers::moveRudderToCenter() {
  // Serial.println("Iniciando verificação de centro");
  _rudderActuator.setM1Speed(0);
  delay(500);
  _currentColor = 0;
  readColor();
  if (_currentColor != 4) {
   while (_currentColor < 4) {
     _rudderActuator.setM1Speed(200);
     readColor();
     // Serial.println(_currentColor);
   }
  }   
  _rudderActuator.setM1Speed(0);
  if (_currentColor != 4) {
   while (_currentColor > 4) {
     _rudderActuator.setM1Speed(-200);
     readColor();
     // Serial.println(_currentColor);
   }
  } 
  _rudderActuator.setM1Speed(0);
  // Serial.println("Leme centralizado com sucesso");
}

void ActuatorsDrivers::readCurrentRGB() {
  tcs.setInterrupt(false);      // liga LED
  delay(60);  // leva 60ms para ler
  tcs.getRawData(&red, &green, &blue, &clear);
  tcs.setInterrupt(true);  // desliga LED

  // Serial.print("C: ");
  // Serial.println(clear);
  // Serial.print("R: ");
  // Serial.println(red);
  // Serial.print("G: ");
  // Serial.println(green);
  // Serial.print("B: ");
  // Serial.println(blue);
}

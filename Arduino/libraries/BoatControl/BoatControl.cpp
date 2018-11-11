/*

  BoatControl.h - Library containing code for the movement controllers used in Nboat project.
  Created by Davi H. dos Santos, March 31, 2018.
  BSD license, all text above must be included in any redistribution.

*/


#include "Arduino.h"
#include "BoatControl.h"

BoatControl::BoatControl(float kp, float ki){
  _kp = kp;
  _ki = ki;
  _starttime = millis(); //TODO check if the time scale is correct (s, ms, micro s ???)
  I_prior = 0;
  _actuators = new wqboatActuatorDrivers();
}

void BoatControl::rudderHeadingControl(SensorManager *sensors, Location target) {
  sensors->setThrusterPower(_actuators->getThrusterPower());

  _currentPosition = sensors->getGPS().location; // TODO in case of exception (or null response...)
  /*Serial.print(_currentPosition.latitude);
  Serial.print(" ");
  Serial.println(_currentPosition.longitude);*/

  _sp = _navFunc.findHeading(_currentPosition, target); //TODO put navigation functions in another library
  //Serial.print(_sp);   Serial.print("--");

  _sp = _navFunc.adjustFrame(_sp);

  _heading = sensors->getIMU().eulerAngles.yaw;

  _currentError = _sp - _heading;
  _currentError = _navFunc.adjustFrame(_currentError);
  _currentError = -_currentError;
  //Serial.print(_currentError);   Serial.print("--");
 
  rudderAngle = P(_currentError) + I(_currentError);
  rudderAngle = rudderAngleSaturation(rudderAngle);
  //Serial.println(rudderAngle);

  _actuators->setRudderAngle(rudderAngle);
  sensors->setThrusterPower(_actuators->getThrusterPower());
}

void BoatControl::rudderVelocityControl(SensorManager *sensors, Location target) {
  sensors->setThrusterPower(_actuators->getThrusterPower());

  _currentPosition = sensors->getGPS().location; // TODO in case of exception (or null response...)

  _sp = _navFunc.findHeading(_currentPosition, target);

  _sp = _navFunc.adjustFrame(_sp);

//  _heading = sensors->getIMU().eulerAngles.yaw;
  _heading = sensors->getGPS().course;

  _currentError = _sp - _heading;
  _currentError = _navFunc.adjustFrame(_currentError);
  //_currentError = -_currentError;
 
  rudderAngle = P(_currentError) + I(_currentError);
  rudderAngle = rudderAngleSaturation(rudderAngle);

  _actuators->setRudderAngle(rudderAngle);
  sensors->setThrusterPower(_actuators->getThrusterPower());
}

float BoatControl::P(float currentError)
{
  return _kp * currentError;
}

float BoatControl::I(float currentError)
{
  _endtime = millis();
  _cycleTime = (_endtime - _starttime)/1000;
  _starttime = millis();
  if ((I_prior > 0 && currentError < 0) || (I_prior < 0 && currentError > 0))
  {
    I_prior = I_prior + _ki * currentError * 5 * _cycleTime;
  }
  else
  {
    I_prior = I_prior + _ki * currentError * _cycleTime;
  }
  return I_prior;
}

float BoatControl::rudderAngleSaturation(float sensor) {
  if (sensor > 90) {
    sensor = 90;
  }
  if (sensor < -90) {
    sensor = -90;
  }
  return sensor;
}

void BoatControl::thrusterControl(SensorManager *sensors, Location target){
  // get distance to target
  sensors->setRudderAngle(_actuators->getRudderAngle());
  _currentPosition = sensors->getGPS().location; // TODO in case of exception (or null response...)

  _distanceToTarget = _navFunc.findDistance(_currentPosition, target);
  
  if (_distanceToTarget > _mediumDistance){
    _actuators->setThrusterPower(100);
  } else if (_distanceToTarget < _mediumDistance && _distanceToTarget > _closeDistance){
    _actuators->setThrusterPower(50);
  } else if (_distanceToTarget < _closeDistance){
    _actuators->setThrusterPower(0);
  } 
}

void BoatControl::thrusterControlWind(SensorManager *sensors){
  // get distance to target
  sensors->setRudderAngle(_actuators->getRudderAngle());
  _actuators->setThrusterPower(map(sensors->getWind().direction, 0, 180, 0, 100));
  //Serial.println(map(sensors->getWind().direction, 0, 180, 0, 100));
}

void BoatControl::initThruster(){
  _actuators->initThruster();
}


/*

  SailboatControl.h - Library containing code for the movement controllers used in Nboat project.
  Created by Davi H. dos Santos, March 31, 2018.
  BSD license, all text above must be included in any redistribution.

*/


#include "Arduino.h"
#include "SailboatControl.h"

SailboatControl::SailboatControl(float kp, float ki){
  _kp = kp;
  _ki = ki;
  _starttime = millis(); //TODO check if the time scale is correct (s, ms, micro s ???)
  I_prior = 0;
  _actuators = new SailboatMiniActuatorDrivers();
}

void SailboatControl::rudderHeadingControl(SensorManager *sensors, Location target) {

  _currentPosition = sensors->getGPS().location;

  //TODO fix this
  _sp = nav.findHeading(_currentPosition, target);
 /* Serial.print("currentLat: "); Serial.print(_currentPosition.latitude, 6);   Serial.print("------");
  Serial.print("currentLon: "); Serial.print(_currentPosition.longitude, 6);   Serial.print("------");
  Serial.print("targetLat: "); Serial.print(target.latitude, 6);   Serial.print("------");
  Serial.print("targettLon: "); Serial.print(target.longitude, 6);   Serial.print("------");
  Serial.print("SP: ");   Serial.print(_sp);   Serial.print("------");*/
  _sp = adjustFrame(_sp);

//  _heading = sensors->getCompass();
    _heading = sensors->getIMU().eulerAngles.yaw;

  /*Serial.print("HEADING: ");
  Serial.print(_heading);
  Serial.print("------");*/

  _currentError = _sp - _heading;
//  _currentError = _heading;
  _currentError = adjustFrame(_currentError);

/*  Serial.print("CURRENTERROR: ");
  Serial.print(_currentError);
  Serial.println("------");*/
  
  // control "equation" (removed) passing the raw error forward
  //rudderAngle = _currentError;

  rudderAngle = P(_currentError) + I(_currentError);
  rudderAngle = rudderAngleSaturation(rudderAngle);
  //rudderAngle_sig = rudder_signal(rudderAngle);

//  Serial.print("RUDDER ANGLE: ");
//  Serial.print(rudderAngle);
//  Serial.print("------");

  _actuators->setRudderAngle(rudderAngle);
  sensors->setSailAngle(_actuators->getSailAngle());
}

float SailboatControl::P(float currentError)
{
  return _kp * currentError;
}

float SailboatControl::I(float currentError)
{
  _endtime = millis();
  _cycleTime = (_endtime - _starttime)/1000;
  _starttime = millis();
 
//  Serial.print("CYCLE TIME: ");
//  Serial.print(_cycleTime);
//  Serial.print("------");
 
  if ((I_prior > 0 && currentError < 0) || (I_prior < 0 && currentError > 0))
  {
    I_prior = I_prior + _ki * 5* currentError * _cycleTime;
  }
  else
  {
    I_prior = I_prior + _ki * currentError * _cycleTime;
  }

//  Serial.print("I PRIOR: ");
//  Serial.print(I_prior);
//  Serial.print("------");
 
  return I_prior;
}

float SailboatControl::adjustFrame(float angle) {
  if (angle > 180) {
    angle = angle - 360;
  }
  if (angle < -180) {
    angle = angle + 360;
  }
  return angle;
}

float SailboatControl::rudderAngleSaturation(float sensor) {
  if (sensor > 90) {
    sensor = 90;
  }
  if (sensor < -90) {
    sensor = -90;
  }
  return sensor;
}

void SailboatControl::sailControl(SensorManager *sensors){
  _windDir = sensors->getWind().direction;
  // angle that I want the sail to have
  _sailAngle =  fabs(_windDir)/2;
  _actuators->setSailAngle(_sailAngle);
  sensors->setRudderAngle(_actuators->getRudderAngle());
   //_actuators->setSailAngle(90);
}

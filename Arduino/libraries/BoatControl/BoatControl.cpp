/*

  BoatControl.h - Library containing code for the movement controllers used in Nboat project.
  Created by Davi H. dos Santos, March 31, 2018.
  BSD license, all text above must be included in any redistribution.

*/


#include "Arduino.h"
#include "BoatControl.h"

BoatControl::BoatControl(){
  _kp = 1;
  _ki = 0;
  _starttime = millis(); //TODO check if the time scale is correct (s, ms, micro s ???)
  I_prior = 0;
}

void BoatControl::rudderHeadingControl(Location target) {

  _currentPosition = _gps.readPosition(); // TODO in case of exception (or null response...)

  _sp = _gps.computeHeading(_currentPosition, target);
  _sp = adjustFrame(_sp);

  _heading = _compass.readHeading();

  _currentError = _sp - _heading;
  _currentError = adjustFrame(_currentError);
  
  // control "equation" (removed) passing the raw error forward
  
  _currentError = rudderAngle;
  rudderAngle = P(_currentError) + I(_currentError);
  rudderAngle = rudderAngleSaturation(rudderAngle);
  //rudderAngle_sig = rudder_signal(rudderAngle);

  _actuators.setRudderPosition(rudderAngle); //TODO

  //rudderAngle_sig = adjustFrame_atuador_cor(rudderAngle); vai pro driver
  //Serial1.print(rudderAngle_sig); vai pro driver
}

float BoatControl::P(float currentError)
{
  return _kp * currentError;
}

float BoatControl::I(float currentError)
{
  _endtime = millis();
  _cycleTime = _endtime - _starttime;
  _starttime = millis();
  if ((I_prior > 0 && currentError < 0) || (I_prior < 0 && currentError > 0))
  {
    I_prior = I_prior + _ki * currentError * 50 * _cycleTime;
  }
  else
  {
    I_prior = I_prior + _ki * currentError * _cycleTime;
  }
  return I_prior;
}

float BoatControl::adjustFrame(float angle) {
  if (angle > 180) {
    angle = angle - 360;
  }
  if (angle < -180) {
    angle = angle + 360;
  }
  return angle;
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

void BoatControl::thrusterControl(Location target, float mediumDistance, float closeDistance){
  // get distance to target
  _currentPosition = _gps.readPosition(); // TODO in case of exception (or null response...)
  _distanceToTarget = _gps.computeDistance(_currentPosition, target);
  
  if (_distanceToTarget > mediumDistance){
    _actuators.setThrusterPower(100);
  } else if (_distanceToTarget < mediumDistance && _distanceToTarget > closeDistance){
    _actuators.setThrusterPower(50);
  } else if (_distanceToTarget < closeDistance){
    _actuators.setThrusterPower(0);
  } 
}

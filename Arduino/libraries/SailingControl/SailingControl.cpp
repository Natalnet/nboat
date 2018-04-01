/*

  SailingControl.h - Library containing code for the movement controllers used in Nboat project.
  Created by Davi H. dos Santos, March 31, 2018.
  BSD license, all text above must be included in any redistribution.

*/


#include "Arduino.h"
#include "SailingControl.h"

SailingControl::SailingControl(){
  _kp = 1;
  _ki = 0;
  _starttime = millis(); //TODO check if the time scale is correct (s, ms, micro s ???)
  I_prior = 0;
}

void SailingControl::rudderHeadingControl(Location target) {

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

  //actuatorsDrivers.rudder(rudderAngle); //TODO

  //rudderAngle_sig = adjustFrame_atuador_cor(rudderAngle); vai pro driver
  //Serial1.print(rudderAngle_sig); vai pro driver
}

float SailingControl::P(float currentError)
{
  return _kp * currentError;
}

float SailingControl::I(float currentError)
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

float SailingControl::adjustFrame(float angle) {
  if (angle > 180) {
    angle = angle - 360;
  }
  if (angle < -180) {
    angle = angle + 360;
  }
  return angle;
}

float SailingControl::rudderAngleSaturation(float sensor) {
  if (sensor > 90) {
    sensor = 90;
  }
  if (sensor < -90) {
    sensor = -90;
  }
  return sensor;
}

void SailingControl::sailControl(){
  _windDir = _windSensors.readWindDirection();
  // angle that i want the sail to have
  _sailAngle =  _windDir/2;
  _actuators.setSailPosition(_sailAngle);
}


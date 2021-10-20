float P_s(float currentError)
{
  return Kp_s * currentError;
}

float I_s(float currentError)
{
  _endtime_s = millis();
  float _cycleTime = (_endtime_s - _starttime_s)/1000;
  _starttime_s = millis();
  if ((I_prior_s > 0 && currentError < 0) || (I_prior_s < 0 && currentError > 0))
  {
    I_prior_s = I_prior_s + Ki_s * currentError * _cycleTime;
  }
  else
  {
    I_prior_s = I_prior_s + Ki_s * currentError * _cycleTime;
  }
  I_prior_s = constrain(I_prior_s, -200, 200);
  return I_prior_s;
}

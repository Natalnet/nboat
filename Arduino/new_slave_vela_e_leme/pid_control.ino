float P_r(float currentError)
{
  return Kp_r * currentError;
}

float I_r(float currentError)
{
  _endtime_r = millis();
  float _cycleTime = (_endtime_r - _starttime_r)/1000;
  _starttime_r = millis();
  if ((I_prior_r > 0 && currentError < 0) || (I_prior_r < 0 && currentError > 0))
  {
    I_prior_r = I_prior_r + Ki_r * currentError * _cycleTime;
  }
  else
  {
    I_prior_r = I_prior_r + Ki_r * currentError * _cycleTime;
  }
  I_prior_r = constrain(I_prior_r, -200, 200);
  return I_prior_r;
}

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

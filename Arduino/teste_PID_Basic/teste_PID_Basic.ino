/********************************************************
 * PID Basic Example
 * Reading analog input 0 to control analog PWM output 3
 ********************************************************/

#include <PID_v1.h>

#define PIN_INPUT 0
#define PIN_OUTPUT 3

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
double Kp=2, Ki=5, Kd=1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT, P_ON_M);

void setup()
{
  //initialize the variables we're linked to
  Input = analogRead(A0);
  Setpoint = 500;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  Serial.begin(9600);
}

void loop()
{
  Input = analogRead(A0);
  myPID.Compute();
  Serial.println(Output);
}

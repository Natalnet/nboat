#include <windSpeed_tst.h>

void windSpeed_tst::rpm_fan() {
  revolutions++;
}

windSpeed_tst::windSpeed_tst()
{
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(1, rpm_fan, FALLING);
  interrupts();
}

void windSpeed_tst::read(){
  readSpeed();
  _windData.speed = mps;
  _windData.direction = readDirection();
}

void windSpeed_tst::readSpeed() {
if (millis() - lastmillis == 1000) { //Update every one second, this will be equal to reading frequency (Hz).
  detachInterrupt(1);//Disable interrupt when calculating
    
    revolutions=Filter.run(revolutions);
    rpm = revolutions * 120; // Convert frequency to RPM, note: 60 works for one interruption per full rotation. For two interrupts per full rotation use half_revolutions * 30.
    Serial.print("RPM =\t"); //print the word "RPM" and tab.
    Serial.print(rpm); // print the rpm value.
    Serial.print("\t Hz=\t"); //print the word "Hz".
    Serial.print(revolutions); //print revolutions per second or Hz. And print new line or enter. divide by 2 if 2 interrupts per revolution
    revolutions = 0; // Restart the RPM counter
    lastmillis = millis(); // Update lastmillis

    mps = 2*3.14*radius*rpm / 60;
    mps = mps * 0.3; // calibration factor for anemometer accuracy, adjust as necessary
    Serial.print("\t M/S=\t"); //print the word "MPH".
    Serial.println(mps);

    attachInterrupt(1, rpm_fan, FALLING); //enable interrupt
}
}

WindData windSpeed_tst::get(){
  return _windData;
}

float windSpeed_tst::readDirection(int windvanePin){
    //windVane read
    float sum = 0;
    for(int i = 0; i < 10; i++){
      windvaneRead = analogRead(A0);
      sum += windvaneRead;
    }
    windvaneRead = sum/10;
  if(windvaneRead >= 770 && windvaneRead <= 810) {windDirection = 0;}
  if(windvaneRead >= 690 && windvaneRead <= 730) {windDirection = 22.5;}
  if(windvaneRead >= 870 && windvaneRead <= 920) {windDirection = 45;}
  if(windvaneRead >= 815 && windvaneRead <= 850) {windDirection = 67.5;}
  if(windvaneRead >= 930 && windvaneRead <= 960) {windDirection = 90;}
  if(windvaneRead >= 590 && windvaneRead <= 615) {windDirection = 112.5;}
  if(windvaneRead >= 620 && windvaneRead <= 640) {windDirection = 135;}
  if(windvaneRead >= 240 && windvaneRead <= 260) {windDirection = 157.5;}
  if(windvaneRead >= 280 && windvaneRead <= 300) {windDirection = 180;}
  if(windvaneRead >= 120 && windvaneRead <= 135) {windDirection = -157.5;}
  if(windvaneRead >= 170 && windvaneRead <= 200) {windDirection = -135;}
  if(windvaneRead >= 50 && windvaneRead <= 74) {windDirection = -112.5;}
  if(windvaneRead >= 87 && windvaneRead <= 100) {windDirection = -90;}
  if(windvaneRead >= 75 && windvaneRead <= 86) {windDirection = -67.5;}
  if(windvaneRead >= 455 && windvaneRead <= 475) {windDirection = -45;}
  if(windvaneRead >= 400 && windvaneRead <= 420) {windDirection = -22.5;}
  if(windDirection < 0) {windDirection = -windDirection;}

  return windDirection;
}

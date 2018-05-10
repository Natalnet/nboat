
long lastWindIRQ=0;
long lastWindChk=0;
long windClickNo=0;

void setup() {
  attachInterrupt(0, wSpeedIRQ, FALLING);
  Serial.begin(9600);
}

void loop() {
  float tst = get_wind_speed();
  if(tst != 0 || tst != NULL){
    Serial.println(tst);
  }
  delay(500);
}

void wSpeedIRQ()
{
  if (!millis()-lastWindIRQ<10)                      //Debounce the wind interrupt switch for 10ms after contact
  {
    lastWindIRQ = millis();                          //Set up last wind interrupt for the next interrupt
    windClickNo++;                                   //Each click per second is 1.492MPH
  }
}

float get_wind_speed()
{
  float windSpeed = 0;
  float dTime = millis()-lastWindChk;    
  dTime /= 1000.0;                                  //Covert ms to sec    
  if (windClickNo != 0) {
  windSpeed = (float)windClickNo / dTime;}     //3 / 0.750s = 4    
  windClickNo = 0;                                  //Reset and start watching for new wind
  lastWindChk = millis();    
  //windSpeed *= 1.492;                               //Calculates the actual wind speed in mph (2 * 1.492 = 2.984mph)    
  return(windSpeed);
}

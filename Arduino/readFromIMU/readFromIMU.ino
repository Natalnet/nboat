void setup() {
        Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
        Serial2.begin(57600);
        delay(500);
}

void loop() {
  float *giro;
  giro = call_IMU(0);
  
  Serial.print(giro[0]); Serial.print(" ");
  Serial.print(giro[1]); Serial.print(" "); 
  Serial.print(giro[2]); Serial.print(" ");
  Serial.println(giro[3]);
}

int call_IMU(int select){
    
  Serial2.begin(57600);
  
  static float call[4];
  while (Serial2.available() <= 0) {
    Serial2.println("#f");
  }
  delay(50);
  if(Serial2.available() > 2) {
  
    call[0] = Serial2.parseFloat();
    call[1] = Serial2.parseFloat();
    call[2] = Serial2.parseFloat();
    call[3] = Serial2.parseFloat();
  
    Serial2.end(); 
  
  }
  return &call;
}

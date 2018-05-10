void setup() {
        Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
        Serial2.begin(57600);
        delay(500);
}

void loop() {
  Serial2.begin(57600);
  
  static float call[3];
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
  
  Serial.print(call[0]); Serial.print(" ");
  Serial.print(call[1]+360); Serial.print(" "); 
  Serial.print(call[2]+360); Serial.print(" ");
  Serial.println(call[3]+360);
}

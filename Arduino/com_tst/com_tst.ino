void setup() {
  Serial1.begin(500000);
  Serial.begin(500000);

}

void loop() {  
  Serial1.println("f");
  delay(100);
  while(Serial1.available()){
    char t = Serial1.read();
    Serial.print(t);
  }
    
  Serial1.println("g");
  delay(100);
  while(Serial1.available()){
    char t = Serial1.read();
    Serial.print(t);
  }
    
  Serial1.println("h");
  delay(100);
  while(Serial1.available()){
    char t = Serial1.read();
    Serial.print(t);
  }
  
  Serial.println();
}

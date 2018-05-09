int call_IMU(int select){
    
  Serial2.begin(57600);
  
    static float call[4]; 
  
    while (Serial2.available() <= 0) {
    Serial2.println("#f");
    
    //int time1 = millis();
    //while((millis()-time1) < 50){}
    
  }
 delay(50);
 if(Serial2.available() > 2) {
   
  call[0] = Serial2.parseFloat();
  call[1] = Serial2.parseFloat();
  call[2] = Serial2.parseFloat();
  call[3] = Serial2.parseFloat();
  
  Serial.print(call[0]); Serial.print(" ");
  Serial.print(call[1]); Serial.print(" ");
  Serial.print(call[2]); Serial.print(" ");
  Serial.println(call[3]);
   
  Serial2.end(); 
   
  }
  return &call;
}

int getGyro() { 
  
  return call_IMU(0);
}

int getMagn() { 
  
  return call_IMU(1);
}

int getAcel() { 
  
  return call_IMU(2);
}

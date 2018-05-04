
int call_IMU(int select){
    
  Serial2.begin(9600);
  
    static int call[2]; 
  
    while (Serial2.available() <= 0) {
    if(select == 0){
    Serial2.println("#vg");}
    if(select == 1){
    Serial2.println("#vm");}
    if(select == 2){
    Serial2.println("#va");}
    
    int time = millis();
    while((millis()-time) < 200){}
    
  }
  
 if(Serial2.available() > 2) {
   
  call[0] = Serial2.parseInt();
  call[1] = Serial2.parseInt();
  call[2] = Serial2.parseInt();
  
   Serial.print("c- "); Serial.print(call[0]); Serial.print(" ");
  Serial.print(call[1]); Serial.print(" "); Serial.println(call[2]);
   
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

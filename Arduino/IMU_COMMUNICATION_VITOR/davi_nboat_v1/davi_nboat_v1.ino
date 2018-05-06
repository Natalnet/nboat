
void setup() {
 
 Serial.begin(9600);
 
}

void loop(){
 
   int *giro;
   giro = getGyro();
   
  Serial.print("g- "); Serial.print(giro[0]); Serial.print(" ");
  Serial.print(giro[1]); Serial.print(" "); Serial.println(giro[2]);
  
   int *mag;
  mag = getMagn();
  
  Serial.print("m- "); Serial.print(mag[0]); Serial.print(" ");
  Serial.print(mag[1]); Serial.print(" "); Serial.println(mag[2]);
  
  int *ace;
  ace = getAcel(); 
  
  Serial.print("a- "); Serial.print(ace[0]); Serial.print(" ");
  Serial.print(ace[1]); Serial.print(" "); Serial.println(ace[2]);
  
}
  




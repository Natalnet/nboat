
void setup() {
 
 Serial.begin(9600);
 Serial2.begin(57600);
 delay(500);
 
}

void loop(){
 
   float *giro;
   giro = getGyro();
   
  //Serial.print("g- "); Serial.print(giro[0]); Serial.print(" ");
  //Serial.print(giro[1]); Serial.print(" "); Serial.println(giro[2]);
  
}


float _IMU__REFERENCE_GYRO[2];  //variavel global do giroscopio
float _IMU__REFERENCE_MAGN[2];  //variavel global do magnetometro
float _IMU__REFERENCE_ACEL[2];  //variavel global do acelerometro

void setup() {
 
 Serial.begin(57600);
 
}

void loop(){
 
   
  getGyro();
   
  Serial.print("g- "); Serial.print(_IMU__REFERENCE_GYRO[0]); Serial.print(" ");  
  Serial.print(_IMU__REFERENCE_GYRO[1]); Serial.print(" "); Serial.println(_IMU__REFERENCE_GYRO[2]);
  
  getMagn();
  
  Serial.print("m- "); Serial.print(_IMU__REFERENCE_MAGN[0]); Serial.print(" ");                                //impressao apenas para referencia
  Serial.print(_IMU__REFERENCE_MAGN[1]); Serial.print(" "); Serial.println(_IMU__REFERENCE_MAGN[2]);
  
  getAcel(); 
  
  Serial.print("a- "); Serial.print(_IMU__REFERENCE_ACEL[0]); Serial.print(" ");                               //impressao apenas para referencia
  Serial.print(_IMU__REFERENCE_ACEL[1]); Serial.print(" "); Serial.println(_IMU__REFERENCE_ACEL[2]);
  
  delay(1000);     //aguarda um segundo
  
}
  



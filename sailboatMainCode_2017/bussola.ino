float dir_bussola(){
  float soma = 0;
  for (int j = 1; j <= 10; j++){
  Wire.beginTransmission(slaveAddress);
  Wire.write("A");
  Wire.endTransmission();
  delay(10);
  Wire.requestFrom(slaveAddress, 2);
  int i = 0;
  while(Wire.available() && i < 2)
  { 
    headingData[i] = Wire.read();
    i++;
  }
  headingValue = headingData[0]*256 + headingData[1];
  heading = headingValue/10;
 //  heading = -heading;
  heading = heading - norte_quadr_buss;
  heading = saturador(heading);
  soma += heading;
  }

 //  delay(100);
  return soma/10;
}

void send_data_master(int corrente, int posicao, int velocidade){
  if (cont_iic % cont_iic_limite == 0){
    Wire.beginTransmission(10);  //slaveAddress
    Wire.write(highByte(corrente)); //I2C is byte oriented; write(a);
    Wire.write(lowByte(corrente));
    Wire.write(highByte(posicao)); //I2C is byte oriented; write(a);
    Wire.write(lowByte(posicao));
    Wire.write(highByte(velocidade)); //I2C is byte oriented; write(a);
    Wire.write(lowByte(velocidade));
    Wire.endTransmission();
  }
}

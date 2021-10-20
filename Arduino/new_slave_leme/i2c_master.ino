void receiveEvent(){
  byte x1, x2;
  x1 = Wire.read();  //x1 hilds upper byte of received a
  x2 = Wire.read();  //x2 holds lower byte of received a
  y1 = (int)x1 << 8 | (int)x2;
  //------------------------
  x1 = Wire.read();  //x1 hilds upper byte of received b
  x2 = Wire.read();  //x2 holds lower byte of received b
  y2 = (int)x1 << 8 | (int)x2;
  //---------------------------
  x1 = Wire.read();  //x1 hilds upper byte of received b
  x2 = Wire.read();  //x2 holds lower byte of received b
  y3 = (int)x1 << 8 | (int)x2;

  corrente_vela_send = y1;
  posicao_vela_send = y2;
  velocidade_vela_send = y3;
  Serial.println(corrente_vela_send);
  Serial.println(posicao_vela_send);
  Serial.println(velocidade_vela_send);
}

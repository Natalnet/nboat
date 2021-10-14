void read_radio(){
  // ler o sinal do rádio
  // mapear para ângulo de atuador
  // passar isso para o controle

  // recebe um sinal entre 1000 - 2000
  channel[0] = pulseIn(11, HIGH); //canal da vela
  //channel[1] = pulseIn(3, HIGH); //canal do leme  
  channel[1] = pulseIn(13, HIGH); //canal do leme
  angulo_leme = map(channel[0], 1000, 2000, -90, 90);
  angulo_vela = map(channel[1], 1000, 2000, 0, 90);
}

// function that runs whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent() {  
  int angle_r;
  int angle_s;
  if (Wire.available()) { // loop through all but the last
    angle_r = Wire.read();    // receive byte as an integer
    angle_s = Wire.read();    // receive byte as an integer
  }
  angle_r = map(angle_r, 0, 179, -90, 90);
  //angle_r -= 95;
  //Serial.println(angle_r);
  leme_controle(constrain(angle_r, -90, 90));
  vela_controle(constrain(angle_s, 0, 90));
  cont++;
  //Serial.println(angle_s);
  //Serial.println();
  //delay(1000);
}

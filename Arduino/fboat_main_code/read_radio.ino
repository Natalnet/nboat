void read_radio(){
  // ler o sinal do rádio
  // mapear para ângulo de atuador
  // passar isso para o controle

  // recebe um sinal entre 1000 - 2000. espera 1 segundo
  channel[0] = pulseIn(28, HIGH); //canal da vela
  channel[1] = pulseIn(26, HIGH); //canal da vela

  if (channel[1] < 1000){
    
  } else {
    radio_vela = channel[1];
  }  
  radio_vela = constrain(radio_vela, 1000, 2000);

  if (channel[0] < 1000){
    
  } else {
    radio_leme = channel[0];
  }  
  radio_leme = constrain(radio_leme, 1000, 2000);
 
  //channel[1] = pulseIn(13, HIGH); //canal do leme  
  //channel[0] = pulseIn(3, HIGH; //canal do leme
  //Serial.println(channel[0]);
  //Serial.println(channel[1]);
  //Serial.println(radio_vela);
  
  //angulo_vela = map(channel[1], 1000, 2000, 0, 90);
  //angulo_leme = map(channel[0], 1000, 2000, -90, 90);
  //channel[0] = 1500;
  angulo_leme = map(radio_leme, 1000, 1950, -90, 90);
  //Serial.println(angulo_leme);
  angulo_vela = map(radio_vela, 1000, 2000, 0, 90);
  angulo_vela = constrain(angulo_vela, 0, 90);
  delay(10);
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
  Serial.println(angle_r);
  leme_controle(constrain(angle_r, -90, 90));
  vela_controle(constrain(angle_s, 0, 90));
  cont++;
  //Serial.println(angle_s);
  //Serial.println();
  //delay(1000);
}

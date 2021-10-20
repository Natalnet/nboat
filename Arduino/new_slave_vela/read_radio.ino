void read_radio(){
  // ler o sinal do rádio
  // mapear para ângulo de atuador
  // passar isso para o controle

  // recebe um sinal entre 1000 - 2000. espera 1 segundo
  channel[1] = pulseIn(52, HIGH); //canal da vela

  if (channel[1] < 1000){
    
  } else {
    radio_vela = channel[1];
  }  
  radio_vela = constrain(radio_vela, 1000, 2000);
  
  //Serial.println(angulo_leme);
  angulo_vela = map(radio_vela, 1000, 2000, 0, 90);
  angulo_vela = constrain(angulo_vela, 0, 90);
  delay(10);
}

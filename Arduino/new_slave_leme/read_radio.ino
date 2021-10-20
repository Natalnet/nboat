void read_radio(){
  // ler o sinal do rádio
  // mapear para ângulo de atuador
  // passar isso para o controle

  // recebe um sinal entre 1000 - 2000. espera 1 segundo
  channel[0] = pulseIn(11, HIGH); //canal do leme

  if (channel[0] < 1000){
    
  } else {
    radio_leme = channel[0];
  }  
  radio_leme = constrain(radio_leme, 1000, 2000);
  delay(10);
}

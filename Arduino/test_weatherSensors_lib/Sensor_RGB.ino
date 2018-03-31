void detecta_cor() {
  uint16_t clear, red, green, blue;
  tcs.setInterrupt(false);      // liga LED
  delay(60);  // leva 60ms para ler
  tcs.getRawData(&red, &green, &blue, &clear);
  tcs.setInterrupt(true);  // desliga LED

  lux = clear;
  r_red = lux / red;
  r_green = lux / green;
  r_blue = lux / blue;

  if(r_red >= 5.5){
    cor = 1; //azul
    // Serial.println("azul");
  } else if((r_blue >= 4) && (r_green <= 3)){
    cor = 2; //amarelo
    // Serial.println("amarelo");
  } else if((lux > 5500 && lux <= 7500) && (r_red >= 3.6 && r_red <= 4.4 ) && (r_green > 3)){
    cor = 3; //roxo
    // Serial.println("roxo");
  } else if((lux <= 3500) && (r_red >= 2.5 && r_red < 3.5)){
    cor = 4; //preto
    // Serial.println("preto");
  } else if((r_blue >= 4.2) && (r_green > 3 && r_green <= 4)){
    cor = 5; //laranja
    // Serial.println("laranja");
  } else if((r_red > 3.5) && (r_green <= 2.8)){
    cor = 6; //verde
    // Serial.println("verde");
  } else if(r_green >= 4){
    cor = 7; //vermelho
    // Serial.println("vermelho");
  } else {
    // Serial.println("nao identificada");
  }  
  
}

void varredura_cores() {
  // Serial.println("Iniciando varredura");
  md.setM1Speed(0);
  delay(1000);
  // Serial.print("A cor atual é :");
  detecta_cor();
  // Serial.println(cor);
  delay(1000);
  while (cor != 7) {
     md.setM1Speed(400);
     detecta_cor();
     // Serial.println(cor);
   }
  md.setM1Speed(0);
  delay(500);
   // Serial.println("Invertendo sentido do motor");
   delay(500);
   // Serial.println("<<<--- Sentido");
   delay(1000);
   while (cor != 1) {
     md.setM1Speed(-400);
     detecta_cor();
     // Serial.println(cor);
   }
  md.setM1Speed(0);
  delay(500);
  // Serial.println("varredura completa");
}

void mostra_rgb() {
  uint16_t clear, red, green, blue;
  tcs.setInterrupt(false);      // liga LED
  delay(60);  // leva 60ms para ler
  tcs.getRawData(&red, &green, &blue, &clear);
  tcs.setInterrupt(true);  // desliga LED

  // Serial.print("C: ");
  // Serial.println(clear);
  // Serial.print("R: ");
  // Serial.println(red);
  // Serial.print("G: ");
  // Serial.println(green);
  // Serial.print("B: ");
  // Serial.println(blue);
}



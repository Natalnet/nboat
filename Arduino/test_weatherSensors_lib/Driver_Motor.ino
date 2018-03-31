void move_leme() {
  espera = 0;
  md.setM1Speed(0);
  detecta_cor();
  while (cor < req_cor) {
    if (req_cor - cor <= 1) { 
    md.setM1Speed(200); } 
    else { 
    md.setM1Speed(400); }
    detecta_cor();
    // Serial.println(cor);
  }
  while (cor > req_cor) {
    if (cor - req_cor <= 1) { 
    md.setM1Speed(-200); } 
    else { 
    md.setM1Speed(-400); }
    detecta_cor();
    // Serial.println(cor);
  }
  while (Serial.available() > 0 ) {
    char t = Serial.read();
  }  
  espera = 1;
  md.setM1Speed(0);
}

void centro() {
  // Serial.println("Iniciando verificação de centro");
  md.setM1Speed(0);
  delay(500);
  cor = 0;
  detecta_cor();
  if (cor != 4) {
   while (cor < 4) {
     md.setM1Speed(200);
     detecta_cor();
     // Serial.println(cor);
   }
  }   
  md.setM1Speed(0);
  if (cor != 4) {
   while (cor > 4) {
     md.setM1Speed(-200);
     detecta_cor();
     // Serial.println(cor);
   }
  } 
  md.setM1Speed(0);
  // Serial.println("Leme centralizado com sucesso");
}


int ler_angulo_atual_r(){
  int pot_r = analogRead(pinoPot_r);

  //Serial.println(pot_r);

  //Serial.println(map(pot_r, pot_min_r, pot_max_r, -90, 90));
  
  //medir pot atuador linear
  return map(pot_r, pot_min_r, pot_max_r, -90, 90);
}

int ler_angulo_atual_s(){
  int pot_s = analogRead(pinoPot_s);
  
  //medir pot guincho
  return map(pot_s, pot_min_s, pot_max_s, 0, 90);
}

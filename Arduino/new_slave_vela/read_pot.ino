int ler_angulo_atual_s(){
  int pot_s = analogRead(pinoPot_s);

  //Serial.println(pot_s);
  
  //medir pot guincho
  return map(pot_s, pot_min_s, pot_max_s, 0, 90);
}

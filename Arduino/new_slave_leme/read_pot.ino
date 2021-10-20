int ler_angulo_atual_r(){
  int pot_r = analogRead(pinoPot_r);

  //Serial.println(pot_r);

  //Serial.println(map(pot_r, pot_min_r, pot_max_r, -90, 90));
  
  //medir pot atuador linear
  return map(pot_r, pot_min_r, pot_max_r, -90, 90);
}

void set_speed_suave(int vel_atual, int vel_ant, int motor){
  // vel_ant -> vel_atual
  // 100 -> 200  = erro 100
  // 100 -> -100 = erro -200
  // vai da velocidade anterior até a atual de forma suave
  // evitar grande pico de corrente
  
  int erro = vel_atual - vel_ant;
  if (abs(erro) > 200){
    if (erro > 0){
      for (int i = vel_ant; i <= vel_atual; i++)
      {
        if (motor == 1){
          md.setM1Speed(i);
        }        
        if (motor == 2){
          md.setM2Speed(i);
        }
        delay(2);
      }
    }
    if (erro < 0){
      for (int i = vel_ant; i >= vel_atual; i--)
      {
        if (motor == 1){
          md.setM1Speed(i);
        }
        
        if (motor == 2){
          md.setM2Speed(i);
        }
        delay(2);
      }
    }
  } else {
    if (motor == 1){
          md.setM1Speed(vel_atual);
    }
    if (motor == 2){
      md.setM2Speed(vel_atual);
    }
  }
}

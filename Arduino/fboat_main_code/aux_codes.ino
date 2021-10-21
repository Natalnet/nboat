void debug_leme(int theta_r_atual, int angulo_leme, int velocidade_motor, float corrente_motor){
  if(cont_leme % cont_limite == 0){
    Serial.print("angulo_atual: ");
    Serial.println(theta_r_atual);
    Serial.print("set_point: ");
    Serial.println(angulo_leme);
    Serial.print("velocidade_motor: ");
    Serial.println(velocidade_motor);
    Serial.print("corrente motor: ");
    Serial.println(corrente_motor);
    Serial.println(); 
  }
}

void debug_vela(int theta_s_atual, int angulo_vela, int velocidade_motor, float corrente_motor){
  if(cont_leme % cont_limite == 0){
    Serial.print("angulo_atual: ");
    Serial.println(theta_s_atual);
    Serial.print("set_point: ");
    Serial.println(angulo_vela);
    Serial.print("velocidade_motor: ");
    Serial.println(vel_acc);
    Serial.print("corrente motor: ");
    Serial.println(corrente_motor);
    Serial.println();
  }
}

// satura para o motor para não ficar consumindo corrente para valores baixos de pwm
int satura_motor(int velocidade_motor, int vel_limite){  
  if(velocidade_motor < vel_limite && velocidade_motor > 0){
    velocidade_motor = 0;
  }
  if(velocidade_motor > -vel_limite && velocidade_motor < 0){
    velocidade_motor = 0;
  }
  return velocidade_motor;
}

void com_pixhawk_vela(float corrente_motor, int theta_s_atual, int velocidade_motor){
  bool aux = (corrente_motor != _corrente_vela_ant || theta_s_atual != _posicao_vela_ant || velocidade_motor != _motor_vela_ant);
  
  // envia mensagem para a pixhawk
  if(cont_vela % cont_limite == 0 && aux){
    send_mavlink(corrente_vela, corrente_motor);
    send_mavlink(posicao_vela, theta_s_atual);
    send_mavlink(motor_vela_com, velocidade_motor);
  
    _corrente_vela_ant = corrente_motor;
    _posicao_vela_ant = theta_s_atual;
    _motor_vela_ant = velocidade_motor;
  
    cont_vela = 0;
  }
}

void com_pixhawk_leme(float corrente_motor, int theta_r_atual, int velocidade_motor){
  bool aux = (corrente_motor != _corrente_leme_ant || theta_r_atual != _posicao_leme_ant || velocidade_motor != _motor_leme_ant);
  
  // envia mensagem para a pixhawk
  if(cont_leme % cont_limite == 0 && aux){
    send_mavlink(corrente_leme, corrente_motor);
    send_mavlink(posicao_leme, theta_r_atual);
    send_mavlink(motor_leme_com, velocidade_motor);
  
    _corrente_leme_ant = corrente_motor;
    _posicao_leme_ant = theta_r_atual;
    _motor_leme_ant = velocidade_motor;
  
    cont_leme = 0;
  }
}

float get_corrente(int motor){
  if (motor == 1){
    return md.getM1CurrentMilliamps()/1000.;
  }
  if (motor == 2){
    return md.getM2CurrentMilliamps()/1000.;
  }
}

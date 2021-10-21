void set_speed_suave(int vel_motor){
  // velocidade atual
  // calcula o erro
  // calcula o PID
  // joga na saída
  int erro = _motor_vela_ant - vel_motor;

  int output = P_m(erro) + I_m(erro);
  Serial.println(output);
  md.setM2Speed(output);
}

void set_speed_incremental(int velocidade_motor){
  int erro = velocidade_motor - vel_acc;
  if(erro > 0){
    vel_acc += vel_incremento;
  }
  if (erro < 0){
    vel_acc -= vel_incremento;
  }
  vel_acc = constrain(vel_acc, -400, 400);
  md.setM2Speed(vel_acc);
  //Serial.println(vel_acc);
}

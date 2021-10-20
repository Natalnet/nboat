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

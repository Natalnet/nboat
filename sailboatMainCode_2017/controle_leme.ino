float saturador(float sensor) {
  if (sensor > 180) {
    sensor = sensor - 360;
  }
  if (sensor < -180) {
    sensor = sensor + 360;
  }
  return sensor;
}

float saturador_rudder(float sensor) {
  if (sensor > 90) {
    sensor = 90;
  }
  if (sensor < -90) {
    sensor = -90;
  }
  return sensor;
}

int saturador_atuador_cor(float sensor) {
  float id = (-sensor + 120)/30;
  int aux = (int)id;
  float decpart = id - aux;
  int idreturn = 1;
  if (decpart <= 0.5){
    idreturn = id;
  } else{
    idreturn = id + 1;
  }
  return idreturn;
}

// controle do rudder
void controle_rudder() {
  sp = saturador(sp);
  erroAtual = sp - heading;
  erroAtual = saturador(erroAtual);
  
  angulo_rudder_ant = angulo_rudder;
  angulo_rudder = 90 * (erroAtual/180);
  
  erroAtual = angulo_rudder;
  angulo_rudder = P() + I();
  angulo_rudder = saturador_rudder(angulo_rudder);
  //angulo_rudder_sig = rudder_signal(angulo_rudder);
  angulo_rudder_sig = saturador_atuador_cor(angulo_rudder);
  Serial1.print(angulo_rudder_sig);
}

float P()
{
  return Kp * erroAtual;
}

float I()
{
  if ((Ianterior > 0 && erroAtual < 0) || (Ianterior < 0 && erroAtual > 0))
  {
    Ianterior = Ianterior + Ki * erroAtual * 50 * tempo_do_ciclo;
  }
  else
  {
    Ianterior = Ianterior + Ki * erroAtual * tempo_do_ciclo;
  }
  return Ianterior;
}

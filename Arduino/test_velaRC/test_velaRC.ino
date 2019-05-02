double channel[3];

void setup() {
  pinMode(34, INPUT); //gear (controle de automático/manual
  pinMode(35, INPUT); //aileron1 (posição da vela)
  pinMode(36, INPUT); //aileron (posição do leme)

}

void loop() {
  // put your main code here, to run repeatedly:
  channel[0] = pulseIn(34, HIGH);
  channel[1] = pulseIn(35, HIGH);
  channel[2] = pulseIn(36, HIGH);

  //mapeia de sinal de rádio para ângulo do leme
  float theta_r_desejado = map(channel[1], 894, 2088, -90, 90); //aileron
  leme_controle(theta_r_desejado);
}

void leme_controle(theta_r_desejado){
  Serial1.print(theta_r_desejado);
}


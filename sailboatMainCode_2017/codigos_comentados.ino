// software on the loop - código controlando simulador
//  void comunicacao() {
//  while (Serial.available()) {
//    character = Serial.read();
//    if (character == ':') {
//      char tab2[1024];
//      strncpy(tab2, content.c_str(), sizeof(tab2));
//      tab2[sizeof(tab2) - 1] = 0;
//      float valor = (float)atof(tab2);
//      dados.push_back(valor);
//      content = "";
//    } else if (character == ';') {
//      biruta = dados.at(0);
//      heading = dados.at(1);
//      currentLocation.latitude = dados.at(2);
//      currentLocation.longitude = dados.at(3);
//      /*Serial.print("I recieved: ");
//      for(int i = 0; i < dados.size(); i++){
//        Serial.print(dados.at(i), 9);
//        Serial.print(" ");
//      }
//      Serial.println();*/
//      vector<float> aux;
//      dados = aux;
//      Serial.println((int)angulo_rudder);
//      //delay(10);
//      Serial.println((int)pos_sail);
//    } else {
//      content.concat(character);
//    }
//  }
//}

// print para testes
//void debug() {
//  if (cont_debug % 10 == 0) {
//    Serial.print("Latitude: ");
//    Serial.print(nextLocation.latitude, 6);
//    Serial.print(" ");
//    Serial.print("Longitude: ");
//    Serial.print(nextLocation.longitude, 6);
//    Serial.print(" ");
//    Serial.print("SP: ");
//    Serial.print(waypointId);
//    Serial.print(" ");
//    Serial.print("Heading: ");
//    Serial.print(waypointBId);
//    Serial.print(" ");
//    Serial.print("Biruta: ");
//    Serial.print(biruta);
//    Serial.print(" ");
//    Serial.print("Bússola: ");
//    Serial.print(biruta);
//    Serial.print(" ");
//    Serial.print("Vela: ");
//    Serial.print(pos_sail);
//    Serial.print(" ");
//    Serial.print("Leme: ");
//    Serial.print(angulo_rudder);
//    Serial.print(" ");
//    Serial.print("Leme ID: ");
//    Serial.print(angulo_rudder_sig);
//    Serial.print(" ");
//    Serial.print("Erro atual: ");
//    Serial.print(erroAtual);
//    Serial.print(" ");
//    Serial.print("DistT: ");
//    Serial.println(distanciaAoDestino);
//  }
//  cont_debug++;
//  if (cont_debug == 500) {
//    cont_debug == 1;
//  }
//}

/*void loop(){

  for(int c = 0; c < 10; c++){
    atualizar_posicao(&startLocation);
    delay(500);
  }

  distanciaInicial = calcular_distancia(&startLocation, &targetLocation);

  // ver como transformar o norte da bússola pro norte da biruta para
  //gerar_pontos(latitudeOrigem, longitudeOrigem, targetLocation.latitude, targetLocation.longitude, biruta, pts_graus, &quant_pts);

  while(~alcancouAlvo){
    atualizar_posicao(&currentLocation);
    heading = dir_bussola();
    sp = calcular_orientacao(&currentLocation, &targetLocation);
    controle_rudder();
    controle_sail();
    distanciaAoDestino = calcular_distancia(&currentLocation, &targetLocation);
    if(distanciaAoDestino <= distanciaInicial){
      aproximando = true;
    }
    else{
      aproximando = false;
    }
    comunicacao();
  }
  alcancouAlvo = false;
}

void comunicacao(){
  //Serial.println(heading, 2);

  if(Serial.available() > 0){ //verifica se existe comunicação com a porta serial
    dado = Serial.read(); //lê os dados da porta serial
    switch(dado){
    case 1:
      latitudeIntermediaria1 = -5.994599;
      longitudeIntermediaria1 = -35.142914;
      latitudeIntermediaria2 = -5.994933;
      longitudeIntermediaria2 = -35.143297;
      latitudeIntermediaria3 = -5.994368;
      longitudeIntermediaria3 = -35.143405;
      break;
    case 2:
      norte_quadr_buss = norte_quadr_buss + 1;
      break;
    case 3:
      norte_quadr_buss = norte_quadr_buss - 1;
      break;
    case 4:
      distanciaAoDestino = distanciaAoDestino + 1;
      break;
    case 5:
      distanciaAoDestino = distanciaAoDestino - 1;
      break;
    }
  }
  else {
    Serial.print(currentLocation.latitude, 6);
    Serial.print(currentLocation.longitude, 6);
    biruta = 100;
    heading = 100;
    Serial.print(biruta+400, 2);
    Serial.print(heading+400, 2);
    Serial.print(startLocation.latitude, 6);
    Serial.print(startLocation.longitude, 6);
    targetLocation = startLocation;
    Serial.print(targetLocation.latitude, 6);
    Serial.print(targetLocation.longitude, 6);
    Serial.print((int)sp+400);
    Serial.print((int)distanciaAoDestino+1000);
    Serial.print((int)distanciaInicial+1000);
  }
}

void comunicacao2(){
  if(Serial.available() > 0){ //verifica se existe comunicação com a porta serial
    if(index < 10) // One less than the size of the array
    {
      inChar = Serial.read(); // Read a character
      inData[index] = inChar; // Store it
      index++; // Increment where to write next
      inData[index] = '\0'; // Null terminate the string
    }
    if(index == 10){
      xCom = strtod(inData,NULL);
      if(contadorCom == 1){
        targetLocation.latitude = xCom;
        index = 0;
        contadorCom++;
        iCom++;
        //        Serial.println(targetLocation.latitude, 6);
      }
      else {
        targetLocation.longitude = -xCom;
        index = 0;
        contadorCom = 1;
        iCom++;
        //        Serial.println(targetLocation.longitude, 6);
      }
    }
  }
}*/

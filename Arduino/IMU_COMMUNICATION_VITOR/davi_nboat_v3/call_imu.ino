
//funcao para aquisicao dos dados da IMU

void call_IMU(int select){
    
  Serial2.begin(57600);  //mesma frequencia da IMU
  
    float call[2];  //vetor responsavel pela aquisicao dos dados;
  
    while (Serial2.available() <= 0) {
    if(select == 0){
    Serial2.println("#vg");}      //envia comando para a IMU pedindo os valores do giroscopio
    if(select == 1){
    Serial2.println("#vm");}    //envia comando para a IMU pedindo os valores do magnetometro
    if(select == 2){
    Serial2.println("#va");}   //envia comando para a IMU pedindo os valores do acelerometro
    
    delay(50);    //espera a coleta de dados
    
  }
  
 if(Serial2.available() > 2) {           //se ja possuem dados disponiveis para serem lidos
   
  call[0] = Serial2.parseFloat();       //primeiro valor no buffer
  call[1] = Serial2.parseFloat();       //segundo valor no buffer
  call[2] = Serial2.parseFloat();       //terceiro valor no buffer
   
  Serial2.end();       //encerra a comunicacao com a IMU
 
 Serial.print("c- "); Serial.print(call[0]); Serial.print(" ");     //imprime na tela os dados recem-chegados apenas para conferencia do usuario
 Serial.print(call[1]); Serial.print(" "); Serial.println(call[2]);  
 
 if(select==0){                                    //atualiza o valor da variavel global do giroscopio 
   
   _IMU__REFERENCE_GYRO[0] = call[0];
   _IMU__REFERENCE_GYRO[1] = call[1];
   _IMU__REFERENCE_GYRO[2] = call[2];
    }
 else if(select==1){                               //atualiza o valor da variavel global do magnetometro
    
   _IMU__REFERENCE_MAGN[0] = call[0];
   _IMU__REFERENCE_MAGN[1] = call[1];
   _IMU__REFERENCE_MAGN[2] = call[2];
  } 
  else if(select==2){                          //atualiza o valor da variavel global do acelerometro
    
    _IMU__REFERENCE_ACEL[0] = call[0];
    _IMU__REFERENCE_ACEL[1] = call[1];
    _IMU__REFERENCE_ACEL[2] = call[2];
  }
 } 
}

int getGyro() {call_IMU(0);}   //atualiza o valor da variavel global do giroscopio

int getMagn() {call_IMU(1);}   //atualiza o valor da variavel global do magnetometro

int getAcel() {call_IMU(2);}  //atualiza o valor da variavel global do acelerometro


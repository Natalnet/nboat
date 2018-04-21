// Código do veleiro maior. GPS, bússola, biruta e cartão sd (shiled ethernet). A cor correspondente
// ao ângulo do leme é enviado para o driver do leme.

#include <StandardCplusplus.h>
#include <serstream>
#include <string>
#include <vector>
#include <iterator>
#include <inttypes.h>
#include <Servo.h>
#include <math.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <Math.h>
#include <Wire.h>
#include <stdio.h>
#include <stdlib.h>
#include <SPI.h>
#include <SD.h>

File dataFile;

#define PI 3.14159265

using namespace std;

//Compass: VCC -> 3,3; SDA -> A4; SCL -> A5;;
//GPS: YELLOW -> GND; ORANGE -> 5V; WITH -> PORTA 2;
//NORTE DA BIRUTA = FRENTE DO BARCO

struct location {
  float latitude;
  float longitude;
};

TinyGPS gps;
int cont_debug = 0;
float start, tempo;

const int buttonPin = 2;
float starttime, endtime;
int buttonState = 0;         // variable for reading the pushbutton status
int buttonState_ant = 0;         // variable for reading the pushbutton status
int cont = 0;
float velocidade_vento;

int recByte;

//variáveis da bússola
int HMC6352Address = 0x42;
int slaveAddress;
byte headingData[2];
int i, headingValue;

float xCom = 0;
char inData[11]; // Allocate some space for the string
char inChar = -1;
byte index = 0;
int contadorCom = 1;
int iCom = 0;
int dado;

//variáveis do GPS

int contador_pontos = 0;

float velocidade;
float direcao;
float distanciaInicial, distanciaPercorrida, lastDistanciaDestino = 0;
float distanciaAoDestino = 99999999;

//variáveis do PID
float erroAtual = 0;    // diferença entre o setpoint e a direção atual do barco
float erroAtualalt = 0;
float erroAnterior = 0;
float Ianterior = 0;    // acumulador do erro integrativo
float Kp = 2;           // ganho proporcional do PID
float Ki = 0.005;       // ganho integrativo do PID
float valor_PID;
float angulo_rudder, angulo_rudder_ant, angulo_rudder_sig;

//tempo aproximado de execução do código
float tempo_do_ciclo = 0.2;

//configurações iniciais
float incremento_sail = 3;
float pos_sail = 60;
boolean aproximando = false;
float teste;

//variáveis de entrada do controle da direção do barco
float heading = 0;  // passada pela bússola
//inserir na hora; alinhar o barco com a direção desejada.
float sp;       // passado pelo algoritmo de einstein (PID - rudder)
float biruta;      // passada pela birtuta
float norte_quadr_buss = 104.00; // tem que calibrar
int birutaPin = A0;
boolean alcancouAlvo = false;

boolean isBordejando = false;
int waypointId = 0, waypointBId = 0, controle = 0;
float angulo_bordejo = 60;
float taxa_dist = 0.2;

location startLocation, currentLocation, lastLocation, nextLocation, targetLocation;

vector<location> waypoints;
vector<location> pontos_bordejar;

vector<float> dados;
String content = "";
char character;

const int chipSelect = 4;

int contador_bug = 0;

vector<location> bordejar(struct location *atual, struct location *destino)
{
  vector<location> pontos_bordejo;

  float heeling = biruta + heading;
  heeling = saturador(heeling);

  float x0 = atual->latitude;
  float y0 = atual->longitude;
  float x = destino->latitude;
  float y = destino->longitude;

  float distancia_bordejar = taxa_dist * distanciaInicial;

  //calcula a reta entre o ponto inicial e de destino
  float a_A = (y - y0) / (x - x0);
  float b_A = y0 - (a_A * x0);
  //float x_temp = x0;
  //float y_temp = a_A * x_temp + b_A;

  if (heeling - heading < 0){
     angulo_bordejo = -angulo_bordejo;
  }

  //float thetaAB = abs(saturador(biruta)) - angulo_bordejo;
  float thetaAB = angulo_bordejo;
  thetaAB = saturador(thetaAB);
  
  //encontra a reta B tal que thetaAB = 45º - biruta e a interseção seja o ponto inicial
  float tan_thetaAB = (float)tan((thetaAB) * (PI / 180));
  float a_B = (a_A - tan_thetaAB) / (tan_thetaAB * a_A + 1);

  float b_B = y0 - (a_B * x0);

  //inicialização de variáveis auxiliares
  float d = distanciaInicial;
  float d_p0 = 9999999;

  float latBord = x;
  float lonBord = y;

  float latProj = x;
  float lonProj = y;

  location pontoProj;

  float latIni = x0;
  float lonIni = y0;
  float latFim = x;
  float lonFim = y;

  while (abs(d - distancia_bordejar) > 1) {
    float latMedia = (latFim + latIni) / 2;
    float lonMedia = (lonFim + lonIni) / 2;

    pontoProj = projecao2d_mod(latMedia, lonMedia, a_A, b_A, a_B, b_B);
    
    d = (float)TinyGPS::distance_between(latMedia, lonMedia, pontoProj.latitude, pontoProj.longitude);

    if (d > distancia_bordejar){
      latFim = latMedia;
      lonFim = lonMedia;
    } else if (d < distancia_bordejar){
      latIni = latMedia;
      lonIni = lonMedia;
    }

    latBord = latMedia;
    lonBord = lonMedia;
  }

  location ponto_projetado = angleToLocation(latBord, lonBord);

  latProj = pontoProj.latitude;
  lonProj = pontoProj.longitude;

  location p0m = projecao2d(latProj, lonProj, a_A, b_A);
  d_p0 = (float)TinyGPS::distance_between(p0m.latitude, p0m.longitude, x0, y0);

  //insere o ponto encontrado no vetor com os pontos do bordejo
  pontos_bordejo.push_back(angleToLocation(latProj, lonProj));

  //encontra as retas paralelas a reta A, onde estão localizados os pontos de bordejo
  float b_linha1 = (-a_A * pontos_bordejo.at(0).latitude + pontos_bordejo.at(0).longitude);
  float y_tira_teima1 = (a_A * pontos_bordejo.at(0).latitude + b_linha1);
  float x_tira_teima1 = (pontos_bordejo.at(0).longitude - b_linha1) / a_A;
  float b_linha2 = 0;

  if (b_linha1 > b_A)
  {
    b_linha2 = b_A - (b_linha1 - b_A);
  }
  else
  {
    b_linha2 = b_A + (b_A - b_linha1);
  }

  //encontrando o número total de pontos de bordejo
  int num_pontos = (int)floor((float)TinyGPS::distance_between(x0, y0, x, y) / d_p0);
  float teste = (float)TinyGPS::distance_between(x0, y0, x, y);

  float delta_x = (p0m.latitude - x0);
  float delta_y = (p0m.longitude - y0);

  float tt_x = x0 + delta_x;
  float tt_y = y0 + delta_y;

  //encontra a projeção dos pontos iniciais nas duas retas paralelas
  location p0l1 = projecao2d(p0m.latitude, p0m.longitude, a_A, b_linha1);
  location p0l2 = projecao2d(p0m.latitude, p0m.longitude, a_A, b_linha2);
  int bom = 1;
  int ruim = 1;

  vector<float> dados;
  String content = "";
  char character;

  for (int z = 1; z < num_pontos; z++)
  {

    float delta_x_temp = z * delta_x;
    float delta_y_temp = z * delta_y;

    if (z % 2 == 0)
    {
      location controle1 = pontos_bordejo.at(z - 1);
      float lat_temp = (float)p0l1.latitude + delta_x_temp;
      float lon_temp = (float)p0l1.longitude + delta_y_temp;
      location controle_loc = angleToLocation(lat_temp, lon_temp);
      pontos_bordejo.push_back(controle_loc);
      bom = z;
    }
    else {
      location controle1 = pontos_bordejo.at(z - 1);
      float aux = abs((heeling - abs(saturador(sp))));
      float delta_xaux = aux * delta_x / 31;
      float delta_yaux = aux * delta_y / 31;
      float lat_temp = p0l2.latitude + delta_x_temp - delta_xaux;
      float lon_temp = p0l2.longitude + delta_y_temp - delta_yaux;
      location controle_loc = angleToLocation(lat_temp, lon_temp);
      pontos_bordejo.push_back(controle_loc);
      ruim = z;
    }
  }
  
  int tamanho_pontos_bordejo = pontos_bordejo.size();

  float d_p0_pu = (float)TinyGPS::distance_between(pontos_bordejo.at(tamanho_pontos_bordejo-1).latitude, pontos_bordejo.at(tamanho_pontos_bordejo-1).longitude, atual->latitude, atual->longitude);
  float d_p0_pd = (float)TinyGPS::distance_between(x0, y0, x, y);

  location aux;
  aux.latitude = destino->latitude;
  aux.longitude = destino->longitude;

  if(d_p0_pu > d_p0_pd){
    pontos_bordejo.at(tamanho_pontos_bordejo-1) = aux;
  } else {
    pontos_bordejo.push_back(aux);
  } 
  
  return pontos_bordejo;
}

void setup()
{
  // escolhendo waypoins
  targetLocation.latitude = 0.0013888888;
  targetLocation.longitude = 0;
  waypoints.push_back(targetLocation);

  targetLocation.latitude = 0.0006944444;
  targetLocation.longitude = 0.0006944444;
  waypoints.push_back(targetLocation);

  targetLocation.latitude = 0;
  targetLocation.longitude = 0;
  waypoints.push_back(targetLocation);

  slaveAddress = HMC6352Address >> 1;
  Serial.begin(9600);  // Comunicação exterior xbee
  Serial1.begin(9600); // Comunicação entre arduinos (receber estação meteorologica e enviar setpoint para o leme)
  //Serial2.begin(9600); 
  Serial3.begin(4800); // GPS
  Wire.begin();       // Bússola  
  starttime = millis();
}

void loop() {
  
  for(int c = 0; c < 10; c++){
    atualizar_posicao(startLocation);
    delay(500);
  }

  lastLocation = currentLocation;
  atualizar_posicao(currentLocation);
  heading = dir_bussola();

  while (1) {
    if (waypoints.size() != 0) {
      if (distanciaAoDestino < 10) {
        if (isBordejando) {
          if (waypointBId < pontos_bordejar.size() - 1) {
            waypointBId += 1;
            nextLocation = pontos_bordejar.at(waypointBId);
          } else {
            isBordejando = false;
            waypointBId = 0;
          }
        } else {
          waypointId += 1;
          waypointId = waypointId % waypoints.size();
          nextLocation = waypoints.at(waypointId);          
        }
      } else {
        if (isBordejando) {
          nextLocation = pontos_bordejar.at(waypointBId);
        } else {
          nextLocation = waypoints.at(waypointId);
        }
      }
      
      if (controle == 0) {
        lastLocation = currentLocation;
        distanciaInicial = calcular_distancia(startLocation, nextLocation);
        controle = 1;
      }
      
      sp = calcular_orientacao(currentLocation, nextLocation);

      lastDistanciaDestino = distanciaAoDestino;
      distanciaAoDestino = calcular_distancia(currentLocation, nextLocation);
      distanciaPercorrida += calcular_distancia(lastLocation, currentLocation);

      controle_rudder();
      
      // caso o veleiro não esteja avançando ao destino. solução: selecionar outro waypoint
      if(distanciaAoDestino >= lastDistanciaDestino){
        if(contador_bug == 0){
          start = millis();
          contador_bug = 1;
        }
      } else {
        contador_bug = 0;
      }

      tempo = millis();

    if((tempo - start) > 20000){
      distanciaAoDestino = 0;
    }

      biruta = wind_dir();
      
      if (abs(biruta) < 30 && !isBordejando && abs(erroAtual) < 5) {
        isBordejando = true;
        pontos_bordejar = bordejar(&lastLocation, &nextLocation);
      }
    }
    lastLocation = currentLocation;
    atualizar_posicao(currentLocation);
    heading = dir_bussola();
    salvar_dados();
  }
}

void enviar_dados_estacaobase(){
  Serial.print('i');
  Serial.print(currentLocation.latitude, 6);
  Serial.print(currentLocation.longitude, 6);
  biruta = 100;
  heading = 101;
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
  Serial.print('f');
}

void salvar_dados(){
  dataFile = SD.open("testecom.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.print(currentLocation.latitude, 6);
    dataFile.print(" ");
    dataFile.print(currentLocation.longitude, 6);
    dataFile.print(" ");
    dataFile.print(startLocation.latitude, 6);
    dataFile.print(" ");
    dataFile.print(startLocation.longitude, 6);
    dataFile.print(" ");
    dataFile.print(nextLocation.latitude, 6);
    dataFile.print(" ");
    dataFile.print(nextLocation.longitude, 6);
    dataFile.print(" ");
    dataFile.print(heading, 2);
    dataFile.print(" ");
    dataFile.print(sp);
    dataFile.print(" ");
    dataFile.print(biruta, 2);
    dataFile.print(" ");
    dataFile.println(distanciaInicial);
    dataFile.print(" ");
    dataFile.print(distanciaAoDestino);
    dataFile.close();
  }
}

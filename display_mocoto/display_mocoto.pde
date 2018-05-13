import processing.serial.*;
Serial myPort;
String response = "";

PFont F; // fonte letras gps
PFont f; // fonte demais textos
  
PShape vento;  //dir_vento
PShape rose;

PImage lagoa;

 // Dados de Sensores de Navegação
    
  float vel_vento = 12;
  float dir_vento = 315;
  float bateria = 78.4;
  float bussola = 180;
  
  float latitude = -6.00536;
  float longitude = -35.12179;
  
 // Dados da qualidade da agua
 
  float[] qualidade = new float[5];
  
 // Variaveis de Controle de Navegação
 
   boolean flag = false;
   float a_leme = 0.0;
   float a_vela = 0.0;
   float passo_vela = 5;
   float passo_leme = 2; 
   
   // mapa - tragetoria
   
   boolean flag_mapa = true;
   boolean flag_trag = false;
   int maps = 0;
   float theta = 0;
   
   float[][] trag = { {240, 180}, {0,0}, {0,0}, {0,0}, {0, 0},
                    {0,0}, {0, 0} };

void setup (){
 
  size(640,480, P2D);
  
  vento = loadShape("compass.svg");
  rose = loadShape("rose.svg");
  
  lagoa = loadImage("lagoa.png");
  
  F = createFont("Arial",22,true); 
  f = createFont("Arial",18,true); 
  
  myPort = new Serial(this, Serial.list()[1],9600);
  printArray(Serial.list());

}
   
void draw(){
  
  frameRate(30);
  background(0,50,120);
  
  if (frameCount % 20 == 0){
      thread("dataTransfer");
}
 
 if(flag_mapa){
  draw_dir_vento(dir_vento); //direcao do vento
  draw_branco(latitude,longitude); //latitude e longitude
  draw_vermelho(qualidade); //vetor de dados
  draw_verde(bateria, vel_vento, dir_vento);
  draw_amarelo();
  draw_mapa();
  draw_barco(bussola,a_vela,a_leme); 
 }
 else{
   draw_mapa();
   draw_amarelo();
   draw_branco(latitude,longitude);
 }
  
}

void keyPressed() {
   
   interacao();
 }
 
void mousePressed() {
  
  if(!flag_mapa) {
    
    f_tragetoria();
    
  }
}
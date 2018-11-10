import processing.serial.*;
import java.io.FileWriter;
import java.io.*;
Serial myPort;
String response = "";

FileWriter fw;
BufferedWriter bw;

PFont F; // fonte letras gps
PFont f; // fonte demais textos
  
PShape vento;  //windDir
PShape rose;

PImage lagoa;
int time_control = 0;

String filename = String.valueOf(day())+"-"+String.valueOf(month())+"-"+String.valueOf(year())+" "+String.valueOf(hour())+":"+String.valueOf(minute())+":"+String.valueOf(second());

 // Dados de Sensores de Navegação
  
float windVel = 12;
float windDir = 315;
float batCharge = 78.4;
float course = 180;
float heading;

float latitude = -6.00536;
float longitude = -35.12179;

// Dados da waterQuality da agua
 
float[] waterQuality = new float[5];

// Variaveis de Controle de Navegação
 
boolean flag = false;
float rudderAngle = 0.0;
float sailAngle = 0.0;
float sailAngleStep = 5;
float rudderAngleStep = 2; 
float speed;
 
// mapa - waypointsetoria

boolean flag_mapa = true;
boolean flag_waypoints = false;
int maps = 0;
float theta = 0;

float pixel_x_min = 30;
float pixel_x_max = 220;
float pixel_y_min = 30;
float pixel_y_max = 280;
float lat_min = 573;
float lat_max = 298;
float lon_min = 284;
float lon_max = 497;

float lat = 417;
float lon = 487;

//-5.839417, -35.201487
//-5.839334, -35.201410
 
int waypointId = -1;
int logState = 0;
//float[][] waypoints = { {240, 180}, {0,0}, {0,0}, {0,0}, {0, 0}, {0,0}, {0, 0} };
float[][] waypoints = { {240, 180}, {260,160}, {280,180}, {0,0}, {0, 0}, {0,0}, {0, 0} };

void setup (){
 
  size(800,640, P2D);
  
  vento = loadShape("compass.svg");
  rose = loadShape("rose.svg");
  
  lagoa = loadImage("reitoria.png");
  //lagoa = loadImage("reitoria.png");
  
  F = createFont("Arial",22,true); 
  f = createFont("Arial",18,true); 
 
  printArray(Serial.list());
  myPort = new Serial(this, Serial.list()[32],9600);
  myPort.clear();

}
   
void draw(){
  
  frameRate(30);
  background(0,50,120);
  
  if (frameCount % 5 == 0){
      thread("dataTransfer");
  }
 
  if(flag_mapa){
    draw_windDir(windDir); //direcao do vento
    draw_position(latitude, longitude); //latitude e longitude
    draw_waterQuality(waterQuality); //vetor de dados
    draw_verde();
    draw_amarelo();
    draw_mapa();
    draw_course(width/2, height/2, 100, course);
    draw_barco(heading,sailAngle,rudderAngle); 
  }
  else{
    draw_mapa();
    draw_amarelo();
    draw_position(latitude, longitude);
  }
}

void keyPressed() {  
   interacao();
}
 
void mousePressed() {
  if(!flag_mapa) {
    //f_waypoints();
  }
}

void draw_verde(){
  
   textFont(f);
   fill(255);
   textAlign(RIGHT);
   
   text("Charge: "+batCharge+"%   ", width-20 ,90);
   text("Wind Spd: "+windVel+" m/s", width-20 ,110);
   text("Wind Dir.: "+windDir+"°", width-20 ,130);
   text("Boat Spd: "+speed+" m/s", width-20 ,150);
   
   noFill();
   strokeWeight(2);
   stroke(0,255,0);
   rect(width-190,10,180,160,7);
}
   
void draw_amarelo(){
  
  String piloto = "ativado"; 
     
  stroke(80);
  strokeWeight(2);
  fill(0,50,120);
  rect(2, 2,320,23,7);
     
  textFont(f);
  fill(255);
  textAlign(LEFT);
   
  text("Trajetória - T | Controle - C | Mapa - M", 5 ,20);
     
  if(flag){
    fill(150,50,50);
    piloto = "Desativado";
  }
  else{
    fill(50,150,50);
    piloto = "Ativado";
  }
  
  stroke(80);
  rect(10,29,245,21,7);
  
  textFont(f);
  fill(255);
  textAlign(LEFT);
   
  text("Piloto Automático "+piloto, 13 , 45);
}


void draw_position(float _latitude, float _longitude){
  
   // Branco - Indicador de posicao gps
 
   // display conteudo branco
   fill(0,50,120);
   stroke(255);
   strokeWeight(2);
   rect(5,height-60,160,50,7);
   
   textFont(F);
  
   fill(255);
   
   textAlign(LEFT);
    
   text(String.format("%.6f", _latitude), 10 ,height-40); //GPS LAT
   text(String.format("%.6f", _longitude), 10 ,height-15); //GPS LON
   
}
     
void draw_waterQuality(float[] _waterQuality){
  //display conteudo vermelho
  textFont(f);
  fill(255);
   
  text("Water Quality", 20 ,100);
  text("P0 = "+_waterQuality[0], 30 ,140);
  text("P1 = "+_waterQuality[1], 30 ,160);
  text("P2 = "+_waterQuality[2], 30 ,180);
  text("P3 = "+_waterQuality[3], 30 ,200);
  text("P4 = "+_waterQuality[4], 30 ,220);
   
  noFill();
  stroke(250,0,0);
  rect(15,80,140,150,7);
}

void draw_windDir(float a) { 
  
  a = a + 45; // a = direcao do vento
  
  int x = width-115; //pox x
  int y = 40; // pos y
  int s = 30; //tamanho
  
  pushMatrix();
  translate(x, y); 
  shape(rose, 45, -22, s+20,s+20);
  fill(0); // cor de fundo
  stroke(0); //cor de borda
  strokeWeight(1); 
  //ellipse(0,0,s*1.5,s*1.5);
  rotate(radians(a));
  shape(vento,-(s/(16/7)),-(s/(16/7)), s,s);
  popMatrix();
}

void draw_mapa(){
  
  if(flag_mapa){
    //image(lagoa,400,320,240,160);
    int alt = 290;
    int larg = 220;
    image(lagoa,width-larg,height-alt,larg,alt);
    
    stroke(200,200,0);
    strokeWeight(7);
   // point(480,370); 
   // point(620,460);
    
    pushMatrix();
    translate(400+map(waypoints[0][0], 0, width, 0, 240),320+map(waypoints[0][1], 0, height, 0, 160));
       
    strokeWeight(7); 
    stroke(50,50,150);
    point(0,0);
       
    if(waypoints[6][1]!=0){
      
      rotate(theta+(PI/2));
      stroke(150,150,50);
      strokeWeight(1);
      line(0,0,map(waypoints[1][0], 0, width, 0, 240),map(waypoints[1][1], 0, height, 0, 160));
     
     for(int i=1;i<6;i++){
       line(map(waypoints[i][0], 0, width, 0, 240),map(waypoints[i][1], 0, height, 0, 160),map(waypoints[i+1][0], 0, width, 0, 240),map(waypoints[i+1][1], 0, height, 0, 160));
     }
       
      strokeWeight(7); 
      stroke(50,50,150);
      point(0,0);
       
      stroke(150,50,50);
      point(map(waypoints[6][0], 0, width, 0, 240),map(waypoints[6][1], 0, height, 0, 160));
         
      stroke(150,150,50);
       
      for(int i=1;i<6;i++){     
        point(map(waypoints[i][0], 0, width, 0, 240),map(waypoints[i][1], 0, height, 0, 160));
      } 
    }
    popMatrix();
  }
  
  else{
    
    image(lagoa,0,0,height,width);
   
    stroke(50,50,150);
    strokeWeight(7); 
    point(waypoints[0][0],waypoints[0][1]);
   
    if(flag_waypoints){
      if(waypoints[6][1]!=0){
        //stroke(200,200,0); 
        pushMatrix();
        translate(waypoints[0][0],waypoints[0][1]);
        rotate(theta+(PI/2));
     
        stroke(150,150,50);
        strokeWeight(1);
        line(0,0,waypoints[1][0],waypoints[1][1]);
   
        for(int i=1;i<6;i++){
          line(waypoints[i][0],waypoints[i][1],waypoints[i+1][0],waypoints[i+1][1]);
        }
   
        strokeWeight(7); 
        stroke(50,50,150);
        point(0,0);
        stroke(150,50,50);
        point(waypoints[6][0], waypoints[6][1]);
        stroke(150,150,50);
   
        for(int i=1;i<6;i++){
          point(waypoints[i][0],waypoints[i][1]);
        } 
   
        popMatrix();
      }  
      strokeWeight(1);
      stroke(150,150,50);
      line(mouseX,0,mouseX,height);
      line(0,mouseY,width,mouseY);
    }
  }
}

void draw_barco(float ang_barco, float ang_vela, float ang_leme){
  
  pushMatrix();
  translate(width/2, height/2);
  rotate(radians(ang_barco));
  
  beginShape();
  
  fill(100);
  stroke(0);
  strokeWeight(1);
  curveVertex(0, -70); // the first control point
  curveVertex(0, -70);
  curveVertex(20, -45); // is also the start point of curve
  curveVertex(30, -10);
  curveVertex(30, -10);
  vertex(30,-10);
  vertex(30,70);
  vertex(-30,70);
  vertex(-30,-10);
  curveVertex(-30, -10);
  curveVertex(-30, -10);
  curveVertex(-20, -45);
  curveVertex(0, -70);
  curveVertex(0, -70);
  
  //vela e leme
   
  endShape(CLOSE);
   
  leme(ang_leme);
  vela(ang_vela);
   
  popMatrix();
}

void leme(float grad){
  pushMatrix();
  translate(0,70);
  rotate(radians(grad));
  stroke(234,138,59);
  strokeWeight(8);
  line(0,0,0,25);
  //line(0,70,0,95);
  popMatrix();
}

void vela(float grad){
  pushMatrix();
  translate(0,-35);
  rotate(radians(grad)); 
  stroke(234,234,2);
  strokeWeight(8);
  line(0,0,0,70);
  //line(0,-35,0,35);
  popMatrix();
}

void draw_course(int cx, int cy, int len, float angle){
  pushMatrix();
  strokeWeight(8);
  stroke(150);
  translate(cx, cy);
  rotate(radians(angle));
  line(0,0,len, 0);
  line(len, 0, len - 15, -15);
  line(len, 0, len - 15, 15);
  popMatrix();
}

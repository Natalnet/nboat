void draw_verde(float bat, float vvento, float dvento){
  
   textFont(f);
   fill(255);
   textAlign(RIGHT);
   
   text("Bateria: "+bat+"%   ", 620 ,90);
   text("Vel. Vento: "+vvento+" nós", 620 ,110);
   text("Dir. Vento: "+dvento+"°", 620 ,130);
   
   noFill();
   stroke(0,255,0);
   rect(455,10,175,140,7);
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


void draw_branco(float lat,float lon){
  
   // Branco - Indicador de posicao gps
 
   // display conteudo branco
   fill(0,50,120);
   stroke(255);
   strokeWeight(2);
   rect(5,height-60,160,50,7);
   
   textFont(F);
  
   fill(255);
   
   textAlign(LEFT);
    
   text(vel_vento, 10 ,height-40); //GPS LAT
   text(vel_vento, 10 ,height-15); //GPS LON
   
   
     }
     
     void draw_vermelho(float[] valor){
   //display conteudo vermelho
   textFont(f);
   fill(255);
   
   text("Qualidade da água", 20 ,120);
   text("P0 = "+valor[0], 30 ,160);
   text("P1 = "+valor[1], 30 ,180);
   text("P2 = "+valor[2], 30 ,200);
   text("P3 = "+valor[3], 30 ,220);
   text("P4 = "+valor[4], 30 ,240);
   
   noFill();
   stroke(250,0,0);
   rect(15,100,170,150,7);
   }

void draw_dir_vento(float a) { 
  
 a = a + 45; // a = direcao do vento
  
 int x = 520; //pox x
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
  image(lagoa,400,320,240,160);
  
  stroke(200,200,0);
  strokeWeight(7);
 // point(480,370); 
 // point(620,460);
  
  pushMatrix();
  translate(400+map(trag[0][0], 0, width, 0, 240),320+map(trag[0][1], 0, height, 0, 160));
     
    strokeWeight(7); 
     stroke(50,50,150);
     point(0,0);
     
     
  if(trag[6][1]!=0){
    
    rotate(theta+(PI/2));
    
   stroke(150,150,50);
   strokeWeight(1);
   line(0,0,map(trag[1][0], 0, width, 0, 240),map(trag[1][1], 0, height, 0, 160));
   
   for(int i=1;i<6;i++){
     
     line(map(trag[i][0], 0, width, 0, 240),map(trag[i][1], 0, height, 0, 160),map(trag[i+1][0], 0, width, 0, 240),map(trag[i+1][1], 0, height, 0, 160));
  
   }
     
     strokeWeight(7); 
     stroke(50,50,150);
     point(0,0);
     
     stroke(150,50,50);
     point(map(trag[6][0], 0, width, 0, 240),map(trag[6][1], 0, height, 0, 160));
     
     stroke(150,150,50);
   
    for(int i=1;i<6;i++){
      
  point(map(trag[i][0], 0, width, 0, 240),map(trag[i][1], 0, height, 0, 160));
  
   } 
  }
  popMatrix();
}
  
  else{
    
   image(lagoa,0,0,width,height);
   
     stroke(50,50,150);
     strokeWeight(7); 
     point(trag[0][0],trag[0][1]);
   
    if(flag_trag){
      if(trag[6][1]!=0){
     //stroke(200,200,0); 
     pushMatrix();
     translate(trag[0][0],trag[0][1]);
     rotate(theta+(PI/2));
     
   stroke(150,150,50);
   strokeWeight(1);
   line(0,0,trag[1][0],trag[1][1]);
   
   for(int i=1;i<6;i++){
   line(trag[i][0],trag[i][1],trag[i+1][0],trag[i+1][1]);
   }
   
     strokeWeight(7); 
     stroke(50,50,150);
     point(0,0);
     
     stroke(150,50,50);
     point(trag[6][0], trag[6][1]);
     
     stroke(150,150,50);
   
    for(int i=1;i<6;i++){
      
   point(trag[i][0],trag[i][1]);
  
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
  translate(320, 240);
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


  
  
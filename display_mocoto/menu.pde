void interacao(){
  
  if(key=='c'){
    
    flag = !flag;
  }
  
  if(key=='m'){
    
  flag_mapa = !flag_mapa;
    
  }
  
  if(key=='t'){
    
    flag_trag = !flag_trag;
    
  }
  
  if(flag){
    
    menu_controle();
  }
}

void menu_controle(){
  
  if(key=='e'){
    
    a_vela = a_vela - passo_vela;
    
    if(a_vela<=-90){a_vela=-90;}
  }
  
 if(key=='q'){
    
    a_vela = a_vela + passo_vela;
    
    if(a_vela>=90){a_vela=90;}
  }
  
  if(key=='d'){
    
    a_leme = a_leme - passo_leme;
    
     if(a_leme<=-90){a_leme=-90;}
  }
  if(key=='a'){
    
    a_leme = a_leme + passo_leme;
    
    if(a_leme>=90){a_leme=90;}
  } 
}

void f_tragetoria(){
  
  /*
  if((mousePressed==true)&&(maps==0)){
    
  //trag[0][0] = 240;//mouseX;
  //trag[0][1] = 180;//mouseY;
  maps = 1;
  }
  else if((mousePressed==true)&&(maps==1)){ */
    
  trag[6][0] = mouseX;
  trag[6][1] = mouseY;
  //maps = 1;
    
    int T = 50;
    int M = 50; 
    
    // m = (trag[6][1]-trag[0][1])/(trag[6][0]-trag[0][0]);
    theta = (trag[6][1]-trag[0][1])/(trag[6][0]-trag[0][0]);//atan(m);
    theta = atan(theta);
    
    if((((trag[6][1]-trag[0][1])<=0)&&((trag[6][0]-trag[0][0])>=0))||((trag[6][1]-trag[0][1])>=0)&&((trag[6][0]-trag[0][0])>=0)){
      
      theta = theta - PI;
    }
    
    trag[6][0] = trag[6][0]-trag[0][0];
    trag[6][1] = trag[6][1]-trag[0][1];
    trag[6][1] = sqrt((trag[6][1]*trag[6][1]) + (trag[6][0]*trag[6][0]));
    trag[6][0] = 0;
    
    for(int i=1;i<6;i++){
      
      M = M*(-1);
    // trag[i][0] = trag[0][0] + (M);
    // trag[i][1] = trag[0][1] + (i*T);
     
     trag[i][0] = (M);
     trag[i][1] = (i*T);
    
  //  maps = 0;
  }
 }
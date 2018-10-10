void interacao(){
  
  if(key=='c'){
    flag = !flag;
  }
  
  if(key=='m'){
    flag_mapa = !flag_mapa;
  }
  
  if(key=='t'){
    flag_waypoints = !flag_waypoints;
  }
  
  if(flag){
    menu_controle();
  }
}

void menu_controle(){
  
  if(key=='e'){
    sailAngle = sailAngle - sailAngleStep;
    
    if(sailAngle<=-90){sailAngle=-90;}
  }
  
 if(key=='q'){
    sailAngle = sailAngle + sailAngleStep;
    
    if(sailAngle>=90){sailAngle=90;}
  }
  
  if(key=='d'){
    rudderAngle = rudderAngle - rudderAngleStep;
    
    if(rudderAngle<=-90){rudderAngle=-90;}
  }
  
  if(key=='a'){
    rudderAngle = rudderAngle + rudderAngleStep;
    
    if(rudderAngle>=90){rudderAngle=90;}
  }
}

//TODO
//mapea de lat-lon para pixel
void angle_to_pixel(){
}

//TODO
//mapea de pixel para lat-lon
void pixel_to_angle(){
}

void f_waypoints(){
  
  /*
  if((mousePressed==true)&&(maps==0)){
    
  //waypoints[0][0] = 240;//mouseX;
  //waypoints[0][1] = 180;//mouseY;
  maps = 1;
  }
  else if((mousePressed==true)&&(maps==1)){ */
    
  waypoints[6][0] = mouseX;
  waypoints[6][1] = mouseY;
  //maps = 1;
    
    int T = 50;
    int M = 50; 
    
    // m = (waypoints[6][1]-waypoints[0][1])/(waypoints[6][0]-waypoints[0][0]);
    theta = (waypoints[6][1]-waypoints[0][1])/(waypoints[6][0]-waypoints[0][0]);//atan(m);
    theta = atan(theta);
    
    if((((waypoints[6][1]-waypoints[0][1])<=0)&&((waypoints[6][0]-waypoints[0][0])>=0))||((waypoints[6][1]-waypoints[0][1])>=0)&&((waypoints[6][0]-waypoints[0][0])>=0)){
      
      theta = theta - PI;
    }
    
    waypoints[6][0] = waypoints[6][0]-waypoints[0][0];
    waypoints[6][1] = waypoints[6][1]-waypoints[0][1];
    waypoints[6][1] = sqrt((waypoints[6][1]*waypoints[6][1]) + (waypoints[6][0]*waypoints[6][0]));
    waypoints[6][0] = 0;
    
    for(int i=1;i<6;i++){
      
      M = M*(-1);
    // waypoints[i][0] = waypoints[0][0] + (M);
    // waypoints[i][1] = waypoints[0][1] + (i*T);
     
     waypoints[i][0] = (M);
     waypoints[i][1] = (i*T);
    
  //  maps = 0;
  }
 }

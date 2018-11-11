void dataTransfer(){
  int QTD_DATA = 10;
    
  if(myPort != null){
    while (myPort.available() > 0) {
      String inBuffer = myPort.readString();
      if (inBuffer != null) {response = inBuffer;}
    }
    //  char inByte = (char) myPort.read();
    //  println(inByte);
    //  if (inByte=='{') {
    //    response = response + inByte;
    //    while (inByte != '}') {
    //      inByte = (char) myPort.read();
    //      response += inByte;
    //      delay(10);
    //    }
    //    //println(response);
    //    myPort.clear();
    //    response = "";
    //  }
    //}
    
    if (response != "") {
      String subStrings[] = new String[QTD_DATA];
      int begin = 0;
      int end = response.length();
      for (int i=0; i<subStrings.length; i++) subStrings[i] = "0";
      
      for (int i=response.length()-1; i>1; i--) {
        if (response.charAt(i)=='}'){
          end = i;
          i = 0;
        }
      } 
      
      for (int i=end; i>1; i--) {
        if (response.charAt(i)=='{'){
          begin = i;
          i = 0;
        }
      }
      
      //println(begin, ", ", end);
      response = response.substring(begin, end+1);
      //println(response);
      //println(response.charAt(0));
      
      if (response.charAt(0) == '{'){
        response = response.replace("{", "");
        response = response.replace("}", "");
        saveData(response);
        subStrings = response.split(",");
        //printArray(subStrings);
        try {
          latitude = Float.parseFloat(subStrings[0]);
          longitude = Float.parseFloat(subStrings[1]);
          heading = Float.parseFloat(subStrings[2]);
          course = Float.parseFloat(subStrings[3]);
          windDir = Float.parseFloat(subStrings[4]);
          //batCharge = Float.parseFloat(subStrings[5]);
          rudderAngle = Float.parseFloat(subStrings[5]);
          sailAngle = Float.parseFloat(subStrings[6]);
          speed = Float.parseFloat(subStrings[7]);
          waypointId = Integer.parseInt(subStrings[8]);
          logState = Integer.parseInt(subStrings[9]);
          //println(windDir);
        }
        catch(NumberFormatException e) {
          //setAlert(e.toString(), "Exception");
              }
        catch(ArrayIndexOutOfBoundsException e) {
          //setAlert(e.toString(), "Exception");
        }
        catch(NullPointerException e){
          //setAlert(e.toString(), "Exception");
        }
      }
      response="";
    }
  }
}

void saveData(String s){
  try{
    File file =new File("/home/davi/Desktop/experimentos/"+filename+".csv");
    if(init == 0){
      init = 1;
      if(!file.exists()){
          file.createNewFile();
        }
 
        FileWriter fw = new FileWriter(file,true);///true = append
        BufferedWriter bw = new BufferedWriter(fw);
        PrintWriter pw = new PrintWriter(bw);
 
        pw.write("Latitude,Longitude,Yaw,Course,WindDir,RudderAngle,SailAngle,Speed,Waypoint,LogState"+"\n");
 
        pw.close();
        startTime = millis();
    }
//chemin = dataPath;
// positions.txt== your file;
 
        if(!file.exists()){
          file.createNewFile();
        }
 
        FileWriter fw = new FileWriter(file,true);///true = append
        BufferedWriter bw = new BufferedWriter(fw);
        PrintWriter pw = new PrintWriter(bw);
        
        //float timeStamp = (millis()-startTime)/1000;
 
        pw.write(s+","+millis()+"\n");
 
        pw.close();
 
 
     }catch(IOException ioe){
         System.out.println("Exception ");
         ioe.printStackTrace();
    }
}

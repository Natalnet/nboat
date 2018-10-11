void dataTransfer(){
  int QTD_DATA = 9;
    
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
      
      for (int i=response.length()-1; i>0; i--) {
        if (response.charAt(i)=='}'){
          end = i;
        }
      }
      
      for (int i=end; i>0; i--) {
        if (response.charAt(i)=='{'){
          begin = i;
        }
      }
      
      println(begin, ", ", end);
      response = response.substring(begin, end+1);
      println(response);
      
      if (response.charAt(0) == '{'){
        response = response.replace("{", "");
        response = response.replace("}", "");
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

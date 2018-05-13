void dataTransfer(){
    int QTD_DATA = 5;
    
  

if(myPort != null){
  if (myPort.available() > 0) {
    char inByte = (char) myPort.read();
    print(inByte);
    if (inByte=='{') {
      response = response + inByte;
      while (inByte != '}') {
        inByte = (char) myPort.read();
        response += inByte;
        delay(100);
        
      }
      print(response);
    }
    
  }
  }

if (response != "") {
      String subStrings[] = new String[QTD_DATA];
      for (int i=0; i<subStrings.length; i++) subStrings[i] = "0";
      response = response.replace("{", "");
      response = response.replace("}", "");
      subStrings = response.split(",");
      printArray(subStrings);
      try {
        bussola = Float.parseFloat(subStrings[0]);
        latitude = Float.parseFloat(subStrings[1]);
        longitude = Float.parseFloat(subStrings[2]);
        vel_vento = Float.parseFloat(subStrings[3]);
        bateria = Float.parseFloat(subStrings[4]);
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
      response="";
    }

}
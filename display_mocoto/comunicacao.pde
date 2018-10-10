void dataTransfer(){
  int QTD_DATA = 9;
    
  if(myPort != null){
    if (myPort.available() > 0) {
      char inByte = (char) myPort.read();
      print(inByte);
      if (inByte=='{') {
        response = response + inByte;
        while (inByte != '}') {
          inByte = (char) myPort.read();
          response += inByte;
          //delay(20);
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
      latitude = Float.parseFloat(subStrings[0]);
      longitude = Float.parseFloat(subStrings[1]);
      heading = Float.parseFloat(subStrings[2]);
      course = Float.parseFloat(subStrings[3]);
      windDir = Float.parseFloat(subStrings[4]);
      batCharge = Float.parseFloat(subStrings[5]);
      rudderAngle = Float.parseFloat(subStrings[6]);
      sailAngle = Float.parseFloat(subStrings[7]);
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
    response="";
  }
}

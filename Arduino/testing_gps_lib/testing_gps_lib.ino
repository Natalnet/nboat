#include "GPS.h"
#include "Location.h"

GPS teste;
Location loc;

void setup(){
}

void loop(){
  loc = teste.readPosition(loc);
}



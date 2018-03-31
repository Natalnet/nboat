#include "Navigation.h"
#include "Location.h"
#include "GPS.h"

vector<Location> tst;
Navigation nav;
Location atual, destino;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  tst = nav.tackingPoints(atual, destino);
}



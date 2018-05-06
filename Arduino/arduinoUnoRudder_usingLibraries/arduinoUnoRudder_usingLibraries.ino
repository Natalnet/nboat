#include "ActuatorsDrivers.h"

ActuatorsDrivers drivers;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  //compiling for arduino uno gives error messasges cause by the use of Serial1
  drivers.getRudderPosition();
}

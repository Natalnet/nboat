#include <myLib.h>

void myLib::irqHandler0() {
  _irqRcvd0 = true;
}

void myLib::irqHandler1() {
  _irqRcvd1 = true;
}

myLib::myLib(uint8_t irqPin)
{
  _irqPin = irqPin;                          // Note: pin 2 = INT0, 3 = INT1
  pinMode(_irqPin, INPUT);
  if (_irqPin == 2) {
    _irqRcvd0 = false;
    attachInterrupt(0, irqHandler0, FALLING);   // Monitor INT0
  } else if (_irqPin == 3) {
    _irqRcvd1 = false;
    attachInterrupt(1, irqHandler1, FALLING);   // Monitor INT1
  }
}

uint8_t myLib::dataAvail() {
  return ((_irqPin == 2 && _irqRcvd0) ||
          (_irqPin == 3 && _irqRcvd1));
}

void myLib::clrIrq() {
  uint8_t sreg;
  sreg = SREG;
  cli();
  if (_irqPin == 2)
    _irqRcvd0 = false;
  else if (_irqPin == 3)
    _irqRcvd1 = false;
  SREG = sreg;
}

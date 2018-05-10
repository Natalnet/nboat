
#ifndef _myLib_h
#define _myLib_h

#include <avr/interrupt.h>
#include <stdint.h>
#include "Arduino.h"

volatile static uint8_t _irqRcvd0;
volatile static uint8_t _irqRcvd1;

class myLib
{
  public:
    myLib(uint8_t irqPin);
    uint8_t dataAvail();
    void clrIrq();
  private:
    uint8_t _irqPin;
    static void irqHandler0();
    static void irqHandler1();
};
#endif

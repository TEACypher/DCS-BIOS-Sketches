#include <Servo.h>

/*
  Tell DCS-BIOS to use a serial connection and use interrupt-driven
  communication. The main program will be interrupted to prioritize
  processing incoming data.
  
  This should work on any Arduino that has an ATMega328 controller
  (Uno, Pro Mini, many others).
 */
#define DCSBIOS_IRQ_SERIAL

#include "DcsBios.h"

/* paste code snippets from the reference documentation here */

DcsBios::Switch2Pos jettStation1("JETT_STATION_1", 10);
DcsBios::Switch2Pos jettStation2("JETT_STATION_2", 9);
DcsBios::Switch2Pos jettStation3("JETT_STATION_3", 8);
DcsBios::LED jettStation1Light(0x7836, 0x0040, 13);
DcsBios::LED jettStation2Light(0x7836, 0x0080, 12);
DcsBios::LED jettStation3Light(0x7836, 0x0100, 11);
void setup() {
  DcsBios::setup();
}

void loop() {
  DcsBios::loop();
}

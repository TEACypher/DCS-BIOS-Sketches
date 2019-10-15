/*
  Tell DCS-BIOS to use a serial connection and use interrupt-driven
  communication. The main program will be interrupted to prioritize
  processing incoming data.
  
  This should work on any Arduino that has an ATMega328 controller
  (Uno, Pro Mini, many others).
 */
#define DCSBIOS_IRQ_SERIAL

#include "DcsBios.h"
#include <Adafruit_SSD1306.h>
#include <splash.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include <Wire.h>
#include <SPI.h>
#include <Servo.h>

/* paste code snippets from the reference documentation here */

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



int LbsLValue[3];                                         //Initialise LbsL display array


void setup() {
  DcsBios::setup();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(4);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.cp437(true);
  display.print("Start");
  display.display();
}

int convertGaugeToInt (float newValue, float maxValue) {              //Converts the value in to a single gigit between 0-9
  return round(newValue/65535*maxValue);

}

void LbsLDisplayPrint(){                                           //Updates the toatl fuel dispaly
  
  display.clearDisplay();
  display.setCursor(0,0);
  display.print (LbsLValue[1]);
  display.print (LbsLValue[2]);
  display.print (LbsLValue[3]);
  display.print ("0");
  display.display();

}
void loop() {
  DcsBios::loop();
  }
  
void onLbsL1Change(unsigned int newValue) {                                         //Generates the 1st digit of the LbsL gauge
  LbsLValue[1] = convertGaugeToInt(newValue, 10);
  LbsLDisplayPrint();
}
DcsBios::IntegerBuffer lbsL1Buffer(0x78bc, 0xffff, 0, onLbsL1Change);                                    

void onLbsL2Change(unsigned int newValue) {
  LbsLValue[2] = convertGaugeToInt(newValue, 10);
  LbsLDisplayPrint();
}
DcsBios::IntegerBuffer lbsL2Buffer(0x78be, 0xffff, 0, onLbsL2Change);

void onLbsL3Change(unsigned int newValue) {
  LbsLValue[3] = convertGaugeToInt(newValue, 10);
  LbsLDisplayPrint();
}
DcsBios::IntegerBuffer lbsL3Buffer(0x78c0, 0xffff, 0, onLbsL3Change);

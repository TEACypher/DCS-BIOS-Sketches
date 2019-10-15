#include <DcsBios.h>

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



int totFuelDisplayValue1;
int totFuelDisplayValue2;
int totFuelDisplayValue3;


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

int convertGaugeToInt (float newValue, float maxValue) {
  return round(newValue/65535*maxValue);

}


void loop() {
  DcsBios::loop();
  }

void onTotFuel1Change(unsigned int newValue) {
  totFuelDisplayValue1 = convertGaugeToInt(newValue, 10);
  display.clearDisplay();
  display.setCursor(0,0);
  display.print (totFuelDisplayValue1);
  display.print (totFuelDisplayValue2);
  display.print (totFuelDisplayValue3);
  display.print ("00");
  display.display();
}
DcsBios::IntegerBuffer totFuel1Buffer(0x78b2, 0xffff, 0, onTotFuel1Change);

void onTotFuel2Change(unsigned int newValue) {
  totFuelDisplayValue2 = convertGaugeToInt(newValue, 10);
  display.clearDisplay();
  display.setCursor(0,0);
  display.print (totFuelDisplayValue1);
  display.print (totFuelDisplayValue2);
  display.print (totFuelDisplayValue3);
  display.print ("00");
  display.display();
}
DcsBios::IntegerBuffer totFuel2Buffer(0x78b4, 0xffff, 0, onTotFuel2Change);

void onTotFuel3Change(unsigned int newValue) {
  totFuelDisplayValue3 = convertGaugeToInt(newValue, 10);
  display.clearDisplay();
  display.setCursor(0,0);
  display.print (totFuelDisplayValue1);
  display.print (totFuelDisplayValue2);
  display.print (totFuelDisplayValue3);
  display.print ("00");
  display.display();
}
DcsBios::IntegerBuffer totFuel3Buffer(0x78b6, 0xffff, 0, onTotFuel3Change);

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



int bingoFuelDisplayValue[2];                                         //Initialise bingo fuel display array

// DcsBios::RotaryEncoder bingoSet("BINGO_SET", "-3200", "+3200", 5, 6);   //Bingo Encoder

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

void bingoFuelDisplayPrint(){                                           //Updates the bingo fuel dispaly
  
  display.clearDisplay();
  display.setCursor(0,0);
  display.print (bingoFuelDisplayValue[1]);
  display.print (bingoFuelDisplayValue[2]);
  display.print ("00");
  display.display();

}
void loop() {
  DcsBios::loop();
  }

void onBingo1Change(unsigned int newValue) {                                    //Generates the 1st digit of the bingo fuel gauge
  bingoFuelDisplayValue[1] = convertGaugeToInt(newValue, 10);
  bingoFuelDisplayPrint();
}
DcsBios::IntegerBuffer bingo1Buffer(0x78cc, 0xffff, 0, onBingo1Change);

void onBingo2Change(unsigned int newValue) {                                    //Generates the 2nd digit of the bingo fuel gauge
  bingoFuelDisplayValue[2] = convertGaugeToInt(newValue, 10);
  bingoFuelDisplayPrint();
  }
DcsBios::IntegerBuffer bingo2Buffer(0x78ce, 0xffff, 0, onBingo2Change);

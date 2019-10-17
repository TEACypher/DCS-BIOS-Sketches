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
#include <U8glib.h>

/* paste code snippets from the reference documentation here */

#define MUX_Address 0x70 // TCA9548A Encoders address               //Define Multiplexer
 


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_FAST);




// Initialize I2C buses using TCA9548A I2C Multiplexer
void tcaselect(uint8_t i2c_bus) {
    if (i2c_bus > 7) return;
    Wire.beginTransmission(MUX_Address);
    Wire.write(1 << i2c_bus);
    Wire.endTransmission(); 
}

void DisplayInit(){
    for (int i = 0; i < 7; i++) {
      tcaselect(i);   // Loop through each connected displays on the I2C buses  
      u8g.firstPage();
      do {
        u8g.begin();  // Initialize display
       } while( u8g.nextPage() );
    }
}

void setup() {
  DcsBios::setup();
  for (int i = 0; i < 7; i++) {
      tcaselect(i);   // Loop through each connected displays on the I2C buses  
      
            // DcsBios::setup();
            display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
            display.clearDisplay();
            display.setTextSize(4);
            display.setTextColor(WHITE);
            display.setCursor(0,0);
            display.cp437(true);
            display.print("Start");
            display.display();
        
      }     
}


      /*===================================Convertion Of Values===========================*/


int convertGaugeToInt (float newValue, float maxValue) {              //Converts the value in to a single gigit between 0-9
  return round(newValue/65535*maxValue);

}




void loop() {
  DcsBios::loop();
  }



      
      /*===========================Updates Bingo Fuel Gauge===========================================*/

      
int OduText[5];                                         //Initialise bingo fuel display array


void OduTextDisplayPrint(){                                           //Updates the bingo fuel dispaly
  
  tcaselect(3);
  display.clearDisplay();
  display.setCursor(0,0);
  display.print (OduText[0]);
//  display.print (bingoFuelDisplayValue[2]);
//  display.print ("00");
  display.display();

}

void onAv8bnaOdu1TextChange(char* newValue) {
    OduText[0];
    OduTextDisplayPrint();
    
}
DcsBios::StringBuffer<4> av8bnaOdu1TextBuffer(0x7962, onAv8bnaOdu1TextChange);

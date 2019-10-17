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


      /*=================================Updates Total Fuel Guage==============================*/


int totFuelDisplayValue[3];                                         //Initialise total fuel display array

void totFuelDisplayPrint(){                                           //Updates the total fuel dispaly
  
  tcaselect(4);
  display.clearDisplay();
  display.setCursor(0,0);
  display.print (totFuelDisplayValue[0]);
  display.print (totFuelDisplayValue[1]);
  display.print (totFuelDisplayValue[2]);
  display.print ("00");
  display.display();

}


void onTotFuel1Change(unsigned int newValue) {                                    //Generates the 1st digit of the total fuel gauge
  totFuelDisplayValue[0] = convertGaugeToInt(newValue, 10);
  totFuelDisplayPrint();
}
DcsBios::IntegerBuffer totFuel1Buffer(0x78b2, 0xffff, 0, onTotFuel1Change);

void onTotFuel2Change(unsigned int newValue) {                                    //Generates the 2nd digit of the total fuel gauge
  totFuelDisplayValue[1] = convertGaugeToInt(newValue, 10);
  totFuelDisplayPrint();
}
DcsBios::IntegerBuffer totFuel2Buffer(0x78b4, 0xffff, 0, onTotFuel2Change);

void onTotFuel3Change(unsigned int newValue) {                                    //Generates the 3rd digit of the total fuel gauge
  totFuelDisplayValue[2] = convertGaugeToInt(newValue, 10);
  totFuelDisplayPrint();
}
DcsBios::IntegerBuffer totFuel3Buffer(0x78b6, 0xffff, 0, onTotFuel3Change);



      /*===============================Updates LbsL Fuel Gauge=====================================*/


int LbsLValue[3];            //Initialise LbsL display array


void LbsLDisplayPrint(){                                           //Updates the LbsL fuel dispaly
  
  tcaselect(3);
  display.clearDisplay();
  display.setCursor(0,0);
  display.print (LbsLValue[0]);
  display.print (LbsLValue[1]);
  display.print (LbsLValue[2]);
  display.print ("0");
  display.display();

}


void onLbsL1Change(unsigned int newValue) {
  LbsLValue[0] = convertGaugeToInt(newValue, 10);
  LbsLDisplayPrint();
}
DcsBios::IntegerBuffer lbsL1Buffer(0x78bc, 0xffff, 0, onLbsL1Change);             //Generates the 1st digit of the LbsL gauge

void onLbsL2Change(unsigned int newValue) {
  LbsLValue[1] = convertGaugeToInt(newValue, 10);
  LbsLDisplayPrint();
}
DcsBios::IntegerBuffer lbsL2Buffer(0x78be, 0xffff, 0, onLbsL2Change);             //Generates the 2nd digit of the LbsL gauge


void onLbsL3Change(unsigned int newValue) {
  LbsLValue[2] = convertGaugeToInt(newValue, 10);
  LbsLDisplayPrint();
}
DcsBios::IntegerBuffer lbsL3Buffer(0x78c0, 0xffff, 0, onLbsL3Change);             //Generates the 3rd digit of the LbsL gauge




      /*==============================Updates LbsR Fuel Gauge=================================*/


int LbsRValue[3];                                                   //Initialise LbsR display array
                                       
void LbsRDisplayPrint(){                                           //Updates the LbsR fuel dispaly
  
  tcaselect(2);
  display.clearDisplay();
  display.setCursor(0,0);
  display.print (LbsRValue[0]);
  display.print (LbsRValue[1]);
  display.print (LbsRValue[2]);
  display.print ("0");
  display.display();

}


void onLbsR1Change(unsigned int newValue) {                                  //Generates the 1st digit of the LbsR gauge
  LbsRValue[0] = convertGaugeToInt(newValue, 10);
  LbsRDisplayPrint();
}
DcsBios::IntegerBuffer lbsR1Buffer(0x78c4, 0xffff, 0, onLbsR1Change);

void onLbsR2Change(unsigned int newValue) {                                  //Generates the 2nd digit of the LbsR gauge
  LbsRValue[1] = convertGaugeToInt(newValue, 10);
  LbsRDisplayPrint();
}
DcsBios::IntegerBuffer lbsR2Buffer(0x78c6, 0xffff, 0, onLbsR2Change);

void onLbsR3Change(unsigned int newValue) {                                  //Generates the 3rd digit of the LbsR gauge
  LbsRValue[2] = convertGaugeToInt(newValue, 10);
  LbsRDisplayPrint();
}
DcsBios::IntegerBuffer lbsR3Buffer(0x78c8, 0xffff, 0, onLbsR3Change);


      
      
      /*===========================Updates Bingo Fuel Gauge===========================================*/

      

int bingoFuelDisplayValue[2];                                         //Initialise bingo fuel display array


void bingoFuelDisplayPrint(){                                           //Updates the bingo fuel dispaly
  
  tcaselect(0);
  display.clearDisplay();
  display.setCursor(0,0);
  display.print (bingoFuelDisplayValue[0]);
  display.print (bingoFuelDisplayValue[1]);
  display.print ("00");
  display.display();

}

void onBingo1Change(unsigned int newValue) {                                    //Generates the 1st digit of the bingo fuel gauge
  bingoFuelDisplayValue[0] = convertGaugeToInt(newValue, 10);
  bingoFuelDisplayPrint();
}
DcsBios::IntegerBuffer bingo1Buffer(0x78cc, 0xffff, 0, onBingo1Change);

void onBingo2Change(unsigned int newValue) {                                    //Generates the 2nd digit of the bingo fuel gauge
  bingoFuelDisplayValue[1] = convertGaugeToInt(newValue, 10);
  bingoFuelDisplayPrint();
  }
DcsBios::IntegerBuffer bingo2Buffer(0x78ce, 0xffff, 0, onBingo2Change);

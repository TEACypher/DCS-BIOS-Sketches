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



      
      /*===========================Updates RPM Gauge===========================================*/

      
int RPMValue[4];                                         //Initialise bingo fuel display array


void RPMDisplayPrint(){                                           //Updates the toatl fuel dispaly

  tcaselect(3);
  display.clearDisplay();
  display.setCursor(0,0);
  display.print (RPMValue[0]);
  display.print (RPMValue[1]);
  display.print (RPMValue[2]);
  display.print (".");
  display.print (RPMValue[3]);
  display.display();

}

void onRpm1Change(unsigned int newValue) {                                    //Generates the 1st digit of the RPM gauge
  RPMValue[0] = convertGaugeToInt(newValue, 10);
  RPMDisplayPrint();
}
DcsBios::IntegerBuffer rpm1Buffer(0x7890, 0xffff, 0, onRpm1Change);

void onRpm2Change(unsigned int newValue) {                                    //Generates the 2nd digit of the RPM gauge
  RPMValue[1] = convertGaugeToInt(newValue, 10);
  RPMDisplayPrint();
}
DcsBios::IntegerBuffer rpm2Buffer(0x7892, 0xffff, 0, onRpm2Change);

void onRpm3Change(unsigned int newValue) {                                    //Generates the 3rd digit of the RPM gauge
  RPMValue[2] = convertGaugeToInt(newValue, 10);
  RPMDisplayPrint();
}
DcsBios::IntegerBuffer rpm3Buffer(0x7894, 0xffff, 0, onRpm3Change);

void onRpm4Change(unsigned int newValue) {                                    //Generates the 4th digit of the RPM gauge
  RPMValue[3] = convertGaugeToInt(newValue, 10);
  RPMDisplayPrint();
}
DcsBios::IntegerBuffer rpm4Buffer(0x7896, 0xffff, 0, onRpm4Change);

      /*===========================Updates Dect Gauge===========================================*/

      
int DuctValue[3];                                         //Initialise Duct display array


void DuctDisplayPrint(){                                           //Updates the Duct display

  tcaselect(4);
  display.clearDisplay();
  display.setCursor(0,0);
  display.print (DuctValue[0]);
  display.print (DuctValue[1]);
  display.print (DuctValue[2]);
  display.display();

}

void onDuct1Change(unsigned int newValue) {
  DuctValue[0] = convertGaugeToInt(newValue, 10);
  DuctDisplayPrint();
}
DcsBios::IntegerBuffer duct1Buffer(0x788a, 0xffff, 0, onDuct1Change);

void onDuct2Change(unsigned int newValue) {
  DuctValue[1] = convertGaugeToInt(newValue, 10);
  DuctDisplayPrint();
}
DcsBios::IntegerBuffer duct2Buffer(0x788c, 0xffff, 0, onDuct2Change);

void onDuct3Change(unsigned int newValue) {
  DuctValue[2] = convertGaugeToInt(newValue, 10);
  DuctDisplayPrint();
}
DcsBios::IntegerBuffer duct3Buffer(0x788e, 0xffff, 0, onDuct3Change);


      /*===========================Updates FF Gauge===========================================*/

      
int FFValue[3];                                         //Initialise FF display array


void FFDisplayPrint(){                                           //Updates the FF display

  tcaselect(2);
  display.clearDisplay();
  display.setCursor(0,0);
  display.print (FFValue[0]);
  display.print (FFValue[1]);
  display.print (FFValue[2]);
  display.display();

}

void onFf1Change(unsigned int newValue) {
  FFValue[0] = convertGaugeToInt(newValue, 10);
  FFDisplayPrint();
}
DcsBios::IntegerBuffer ff1Buffer(0x7898, 0xffff, 0, onFf1Change);

void onFf2Change(unsigned int newValue) {
  FFValue[1] = convertGaugeToInt(newValue, 10);
  FFDisplayPrint();

}
DcsBios::IntegerBuffer ff2Buffer(0x789a, 0xffff, 0, onFf2Change);

void onFf3Change(unsigned int newValue) {
  FFValue[2] = convertGaugeToInt(newValue, 10);
  FFDisplayPrint();

}
DcsBios::IntegerBuffer ff3Buffer(0x789c, 0xffff, 0, onFf3Change);


      /*===========================Updates JPT Gauge===========================================*/

      
int JPTValue[3];                                         //Initialise JPT display array


void JPTDisplayPrint(){                                           //Updates the JPT display

  tcaselect(0);
  display.clearDisplay();
  display.setCursor(0,0);
  display.print (JPTValue[0]);
  display.print (JPTValue[1]);
  display.print (JPTValue[2]);
  display.display();

}

void onJpt1Change(unsigned int newValue) {
  JPTValue[0] = convertGaugeToInt(newValue, 10);
  JPTDisplayPrint();
}
DcsBios::IntegerBuffer jpt1Buffer(0x789e, 0xffff, 0, onJpt1Change);


void onJpt2Change(unsigned int newValue) {
  JPTValue[1] = convertGaugeToInt(newValue, 10);
  JPTDisplayPrint();
}
DcsBios::IntegerBuffer jpt2Buffer(0x78a0, 0xffff, 0, onJpt2Change);

void onJpt3Change(unsigned int newValue) {
  JPTValue[2] = convertGaugeToInt(newValue, 10);
  JPTDisplayPrint();
}
DcsBios::IntegerBuffer jpt3Buffer(0x78a2, 0xffff, 0, onJpt3Change);


      /*===========================Updates H20 Gauge===========================================*/

      
int H20Value[2];                                         //Initialise H20 display array


void H20DisplayPrint(){                                           //Updates the H20 display

  tcaselect(6);
  display.clearDisplay();
  display.setCursor(0,0);
  display.print (H20Value[0]);
  display.print (H20Value[1]);
  display.print ("0");
  display.display();

}

void onH2o1Change(unsigned int newValue) {
  H20Value[0] = convertGaugeToInt(newValue, 10);
  H20DisplayPrint();
}
DcsBios::IntegerBuffer h2o1Buffer(0x78aa, 0xffff, 0, onH2o1Change);

void onH2o2Change(unsigned int newValue) {
  H20Value[1] = convertGaugeToInt(newValue, 10);
  H20DisplayPrint();
}
DcsBios::IntegerBuffer h2o2Buffer(0x78ac, 0xffff, 0, onH2o2Change);

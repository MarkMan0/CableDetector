
#define DISP_ADDR   (0x3C)


#include <Arduino.h>
#include "ADC_ADS1015.h"

#include "Adafruit_SSD1306.h"



#define DEBUG 1

//variable to be used in the ISR
float reading; 


ADC_ADS1015 adc;

Adafruit_SSD1306 disp(128, 64);


void setup() {
  
  #ifdef DEBUG
    Serial.begin(115200);
  #endif


  disp.begin(SSD1306_SWITCHCAPVCC, DISP_ADDR);
  disp.clearDisplay();
  disp.setTextColor(WHITE);
  disp.display();
  adc.startContinuous(MUXA0A1, PGA02, DR3300);
  reading = 0.0;
  //TODO: set up timerX for discrete sampling

}

void loop() {
  
  //a reading is taken every loop, can't be done in an ISR, because it freezes the code
  //TODO: solve it
  reading = adc.readVolts();    

  disp.setCursor(0,1);
  disp.setTextSize(2);
  
  disp.println("TEST");
  disp.display();

  #ifdef DEBUG
    Serial.print("reading: ");
    Serial.println(reading);
  #endif

}
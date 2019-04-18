#include <Arduino.h>
#include "ADC_ADS1015.h"

#define DEBUG 1

//variable to be used in the ISR
float reading; 


ADC_ADS1015 adc;



void setup() {
  
  #ifdef DEBUG
    Serial.begin(115200);
  #endif


  adc.startContinuous(MUXA0A1, PGA02, DR3300);
  reading = 0.0;
  //TODO: set up timerX for discrete sampling

}

void loop() {
  
  //a reading is taken every loop, can't be done in an ISR, because it freezes the code
  //TODO: solve it
  reading = adc.readVolts();    
  
  #ifdef DEBUG
    Serial.print("reading: ");
    Serial.println(reading);
  #endif

}
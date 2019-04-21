
#define DISP_ADDR   (0x3C)

#include "interrupt.h"
double freq = 0.0;
unsigned long last = 0;


#include <Arduino.h>
#include "ADC_ADS1015.h"

#include "Adafruit_SSD1306.h"



#define DEBUG 1

//variable to be used in the ISR
float reading; 


ADC_ADS1015 adc;

Adafruit_SSD1306 disp(128, 64);

struct Fourier {
  double s, c;
};

Fourier fourier;

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
  
  //setup interrupt for timer2
  cli(); // stop interrupts
  TCCR2A = 0; // set entire TCCR2A register to 0
  TCCR2B = 0; // same for TCCR2B
  TCNT2  = 0; // initialize counter value to 0
  // set compare match register for 1000 Hz increments
  OCR2A = 249; // = 16000000 / (64 * 1000) - 1
  // turn on CTC mode
  TCCR2B |= (1 << WGM22);
  // Set CS22, CS21 and CS20 bits for 64 prescaler
  TCCR2B |= (1 << CS22) | (0 << CS21) | (0 << CS20);
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);
  sei(); // allow interrupts
}

void loop() {
  
  //a reading is taken every loop, can't be done in an ISR, because it freezes the code
  //TODO: solve it
  Serial.println(freq);
  return;

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


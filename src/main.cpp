
#define DISP_ADDR   (0x3C)

#define TS (1.0/5000.0)

#define READING_CNT   (5000)

struct Fourier {
  double s, c;
  unsigned long count = 0;
};

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
  TCCR1A = 0; // set entire TCCR2A register to 0
  TCCR1B = 0; // same for TCCR2B
  TCNT1  = 0; // initialize counter value to 0
  // set compare match register for 1000 Hz increments
  OCR1A = 999; // = 16000000 / (8 * 5000) - 1
  
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS22, CS21 and CS20 bits for 32 prescaler
  TCCR1B |= (1 << CS11) | (0 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei(); // allow interrupts
}

void loop() {
  
  //a reading is taken every loop, can't be done in an ISR, because it freezes the code
  //TODO: solve it
  
  if(fourier.count > READING_CNT) {
    //cli();  //stop interrupt
    TCNT1  = 0; //reset counter

    float magn = 1000000*sqrt(fourier.c*fourier.c + fourier.s*fourier.s);

    disp.setCursor(0,1);
    disp.setTextSize(2);
  
    disp.println("TEST");
    disp.display();
    Serial.println(magn);
    fourier.c = 0;
    fourier.s = 0;
    fourier.count = 0;
    //sei();
  }
  
  reading = adc.readVolts();    

  

}


#include <Arduino.h>

extern double freq;
extern unsigned long last;

ISR(TIMER2_COMPA_vect){
    freq = 1000000.0/(micros() - last);
    last = micros();
}
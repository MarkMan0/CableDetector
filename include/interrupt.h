#include <Arduino.h>

extern double freq;
extern unsigned long last;

extern Fourier fourier;
extern float reading;

ISR(TIMER1_COMPA_vect){
    fourier.c += reading*cos(2.0*PI*50.0*fourier.count*TS) * TS;
    fourier.s += reading*sin(2.0*PI*50.0*fourier.count*TS) * TS;
    ++fourier.count;
}
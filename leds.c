#include "leds.h"
#include "general.h"
#include <xc.h>
#include <pic18f4331.h>

void moving_leds(){
              PORTBbits.RB0 = 1;
              delay(80);
              PORTBbits.RB1 = 1;
              delay(60);
              PORTBbits.RB2 = 1;
              delay(70);
              PORTBbits.RB3 = 1;
              delay(90);
              PORTBbits.RB0 = 0;
              PORTBbits.RB1 = 0;
              PORTBbits.RB2 = 0;
              PORTBbits.RB3 = 0;
              delay(90);
       }

void blink_leds(){
              PORTBbits.RB0 = 1;
              PORTBbits.RB1 = 1;
              PORTBbits.RB2 = 1;
              PORTBbits.RB3 = 1;
              delay(100);
              PORTBbits.RB0 = 0;
              PORTBbits.RB1 = 0;
              PORTBbits.RB2 = 0;
              PORTBbits.RB3 = 0;
              delay(90);
}

void on_low(){
    PORTBbits.RB0 = 1;
}

/*
 * File:   Button_LEDS.c
 * Author: Lacy
 *
 * Created on April 4, 2019, 12:46 PM
 */


#include <stdio.h>
#include <stdlib.h>
#include<stdint.h>

#include <xc.h>
#include "leds.h"
#include "general.h"
#include <xc.h>
#include <pic18f4331.h>

#define _XTAL_FREQ 80000
void button_LEDS () {
  TRISBbits.TRISB0 = 1; //RB0 as input PIN for button press
  TRISBbits.TRISB1 = 1; //RB1 as input PIN for button press
  TRISBbits.TRISB2 = 1; //RB2 as input PIN for button press
	
  int status;
 do{
    status = PORTBbits.RB0;         // Read the pin for LED
    __delay_ms(10);                   // Introduce a delay between each read
    status = PORTBbits.RB1;         // Read the pin for LED
    __delay_ms(10);                   // Introduce a delay between each read
    status = PORTBbits.RB2;         // Read the pin for LED
    __delay_ms(10);                   // Introduce a delay between each read
}while(status);                     // Keep reading till a HIGH
    return;
}

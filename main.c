/*
 * File:   main.c
 * Author: Josh
 *
 * Created on March 18, 2019, 7:12 PM
 */
// CONFIG1H

#include "general.h"

#include <xc.h>
#include <pic18f4331.h>
#include <stdio.h>

#include "seven-segment.h"
#include "leds.h"
unsigned char counter=0;//Overflow counter

void clear_leds(){
    PORTBbits.RB0 =0; 
    PORTBbits.RB1 =0; 
    PORTBbits.RB2 =0; 
    PORTBbits.RB3 =0; 
}
// interrupt address is 0x08
__interrupt() void ISR(void){ 
    // https://www.electronicwings.com/pic/pic18f4550-timer
    //    if(TMR0IE && TMR0IF){
    TMR1=0xF856;

    clear_leds();
    _clear_all();
    switch(counter % 4){
        case 0: 
            PORTBbits.RB0 = 1; 
            break;
        case 1: 
            PORTBbits.RB1 = 1; 
            break;
        case 2: 
            PORTBbits.RB2 = 1; 
            break;
        case 3: 
            PORTBbits.RB3 = 1; 
            break;
    }

        switch(counter){ // 8-segment display
            case 0:
                PORTAbits.RA0 = 1;
                break;
            case 1:
                PORTAbits.RA1 = 1;
                break;
            case 2:
                PORTAbits.RA2 = 1;
                break;
            case 3:
                PORTEbits.RE0 = 1;
                break;
            case 4:
                PORTAbits.RA3 = 1;
                break;
            case 5:
                PORTAbits.RA4 = 1;
                break;
            case 6:
            PORTAbits.RA5 = 1;
                break;
        }

    if(++counter > 6)
        counter = 0;

    PIR1bits.TMR1IF=0;  /* Make Timer1 Overflow Flag to '0' */
    //    }
}

void init_interrupts(){
    //https://openlabpro.com/guide/interrupt-handling-in-pic18f4550/
    //SETUP TIMER0 
    GIE=1;		/* Enable Global Interrupt */
    PEIE=1;  		/* Enable Peripheral Interrupt */
    TMR1IE=1;		/* Enable Timer1 Overflow Interrupt */
    TMR1IF=0;

    /* Enable 16-bit TMR1 register,no pre-scale,internal clock, timer OFF */
    T1CON=0x80;		

    TMR1=0xF856;	/* Load Count for generating delay of 1ms */
    TMR1ON=1;		/* Turn ON Timer1 */
}
void init(){
    TRISBbits.RB0 = 0;
    TRISBbits.RB1 = 0;
    TRISBbits.RB2 = 0;
    TRISBbits.RB3 = 0;
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB3 = 0;

    init_interrupts();
    init_seven_segment();
}
/* ****************** MAIN ****************** */
void main(void){
    init();
    blink_leds();
    while (1){        
        PORTAbits.RA0 = 1;
        PORTAbits.RA1 = 1;
        PORTAbits.RA2 = 1;
        PORTAbits.RA3 = 1;

        CLRWDT();
    }

}



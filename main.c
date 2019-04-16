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
#include <limits.h>
#include <stdio.h>

#include "seven-segment.h"
#include "leds.h"
unsigned int counter=0,
        counter_ms =0, 
        counter_seg = 0, 
        is_emergency = 0;
void clear_leds(){
    PORTBbits.RB0 =0; 
    PORTBbits.RB1 =0; 
    PORTBbits.RB2 =0; 
    PORTBbits.RB3 =0; 
}

void set_fan(int value){
    PORTBbits.RB4 = value;
}
// interrupt address is 0x08
__interrupt() void ISR(void){ 
    // https://www.electronicwings.com/pic/pic18f4550-timer

    if (INTCON3bits.INT1F == 1){
        is_emergency = ~ is_emergency;
        INTCON3bits.INT1F = 0;
    }
    else if ( !is_emergency && INTCONbits.INT0IF == 1) {
        if (++counter_seg > 3){
            counter_seg = 0;
        }
        INTCONbits.INT0F = 0;
    }

    TMR1=0xF856;
    clear_leds();
    _clear_all();

    if(is_emergency){
        emergency(counter_ms);
        PORTBbits.RB3 = 1; 
        set_fan(0);
        switch(counter_ms % 3){
            case 0:
                PORTBbits.RB2 = 1;
                break;
            case 1:
                PORTBbits.RB1 = 1; 
                break;
            case 2:
                PORTBbits.RB0 = 1; 
                break;
        }
    }
    else{
        switch(counter_seg){
            case 0: 
                zero(counter_ms);
                set_fan(0);
                break; 
            case 1: 
                one(counter_ms);
                PORTBbits.RB0 = 1; 
                set_fan(1);
                break;
            case 2: 
                two(counter_ms);
                PORTBbits.RB1 = 1; 
                set_fan(1);
                break;
            case 3: 
                three(counter_ms);
                PORTBbits.RB2 = 1; 
                set_fan(1);
                break;
        }
    }
    if(++counter_ms == INT_MAX){
        counter_ms = 0;
    }

    PIR1bits.TMR1IF=0;  /* Make Timer1 Overflow Flag to '0' */
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

void  External_Interrupt_Init(){
    TRISCbits.TRISC3 = 1; /* Make INT0 pin as an input pin*/    
    TRISCbits.TRISC4 = 1; /* Make INT1 pin as an input pin*/

    //    INTCON2=0x00;		/* Set Interrupt on falling Edge*/
    INTCON2 = 0x80;
    INTCONbits.INT0IF=0;	/* Clear INT0IF flag*/
    INTCONbits.INT0IE=1;	/* Enable INT0 external interrupt*/

    INTCON3bits.INT1IF=0;	/* Clear INT1IF flag*/
    INTCON3bits.INT1IE=1;	/* Enable INT1 external interrupt*/
    /*
    * Interupt 2 
    */

    INTCONbits.GIE=1;		/* Enable Global Interrupt*/
}

void init(){
    TRISBbits.RB0 = 0;
    TRISBbits.RB1 = 0;
    TRISBbits.RB2 = 0;
    TRISBbits.RB3 = 0;
    TRISBbits.RB4 = 0;
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB3 = 0;
    TRISBbits.TRISB4 = 0;
    set_fan(0);
    External_Interrupt_Init();
    init_interrupts();
    init_seven_segment();
}
/* ****************** MAIN ****************** */
void main(void){
    unsigned int duty_cycle;  
    char __1, // don't care
         __2, 
         __3,
         temputure_val_dec,
         checksum;

    OSCCON=0x72;         /* set internal clock to 8MHz */
    TRISCbits.TRISC2=0;  /* Set CCP1 pin as output for PWM out */
    PR2=199;             /* load period value in PR2 register */ 
    CCPR1L=1;            /* load duty cycle */
    T2CON=0;             /* no pre-scalar,timer2 is off */
    TMR2=0;

    init();
    T2CONbits.TMR2ON=1;  /* Turn ON Timer2 */

    blink_leds();
    while (1);

}



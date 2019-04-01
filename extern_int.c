/*
 * File:   extern_int.c
 * Author: Lacy
 *
 * Created on March 29, 2019, 6:34 PM
 */



void main(void) {
    return;
}
void External_Interrupt_Init()
{
    TRISBbits.TRISB0=1;		/* Make INT0 pin as an input pin*/
    
    /* Also make PBADEN off in Configuration file or clear ADON 
    in ADCON0 so as to set analog pin as digital*/

    INTCON2=0x00;		/* Set Interrupt detection on falling Edge*/
    INTCONbits.INT0IF=0;	/* Clear INT0IF flag*/
    INTCONbits.INT0IE=1;	/* Enable INT0 external interrupt*/
    INTCONbits.GIE=1;		/* Enable Global Interrupt*/
}

 


 
/*
*Toggle LED using External Interrupt
*www.electronicwings.com
*/

#include <xc.h>
#include "osc.h"
#include <p18f4550.h>

#define LED LATC

void External_Interrupt_Init();
void MSdelay(unsigned int);

void main()
{
    OSCCON=0x72;		/* Set internal oscillator to 8MHz*/
    TRISC0=0;			/* Make PORTC.0 as output*/
    LED=0;            
    External_Interrupt_Init();	/* Initialize External Interrupt*/   
    while(1);
}

void External_Interrupt_Init()
{
    TRISBbits.TRISB0=1;		/* Make INT0 pin as an input pin*/

    /* Also make PBADEN off in Configuration file or
    clear ADON in ADCON0 so as to set analog pin as digital*/
  
    INTCON2=0x00;		/* Set Interrupt on falling Edge*/
    INTCONbits.INT0IF=0;	/* Clear INT0IF flag*/
    INTCONbits.INT0IE=1;	/* Enable INT0 external interrupt*/
    INTCONbits.GIE=1;		/* Enable Global Interrupt*/
}


void interrupt ISR()
{   
    LED = ~(LED);		/* Toggle LED on interrupt*/
    MSdelay(200);
    INTCONbits.INT0IF=0;
}

void MSdelay(unsigned int val)
{
 unsigned int i,j;
 for (i=0; i<val; i++)
     for (j=0; j<165; j++);	/* Delay count for 1ms for 8MHz freq. */
}

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
unsigned int counter=0,counter_ms =0, counter_seg = 0;//Overflow counter
void clear_leds(){
    PORTBbits.RB0 =0; 
    PORTBbits.RB1 =0; 
    PORTBbits.RB2 =0; 
    PORTBbits.RB3 =0; 
}
// interrupt address is 0x08
__interrupt() void ISR(void){ 
    // https://www.electronicwings.com/pic/pic18f4550-timer
    TMR1=0xF856;
    clear_leds();
    _clear_all();

    switch(counter_seg){
        case 0: 
            break; // do nothing

        case 1: 
            one(counter_ms);
            PORTBbits.RB0 = 1; 
            break;
        case 2: 
            two(counter_ms);
            PORTBbits.RB1 = 1; 
            break;
        case 3: 
            three(counter_ms);
            PORTBbits.RB2 = 1; 
            break;
        case 4: 
            emergency(counter_ms);
            PORTBbits.RB3 = 1; 
            break;
    }
    if (counter_ms % 1000 == 0){
        if (++counter_seg > 4){
            counter_seg = 0;
        }
    }
    if(++counter_ms == INT_MAX)
    {
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
#define Data_Out LATE0
#define Data_In PORTEbits.RE1
#define Data_Dir TRISEbits.RE1

void init_DHT11(){
    // https://www.electronicwings.com/pic/dht11-sensor-interfacing-with-pic18f4550
    Data_Dir = 0;  /* set as output port */
    Data_Out = 0;  /* send low pulse of min. 18 ms width */
    __delay_ms(18);
    Data_Out = 1;  /* pull data bus high */
    __delay_us(20);
    Data_Dir = 1;  /* set as input port */  
}

void DHT11_CheckResponse()
{
    while(Data_In & 1);  /* wait till bus is High */     
    while(!(Data_In & 1));  /* wait till bus is Low */
    while(Data_In & 1);  /* wait till bus is High */
}

char DHT11_ReadData()
{
    char i,data = 0;  
    for(i=0;i<8;i++)
    {
        while(!(Data_In & 1));  /* wait till 0 pulse, this is start of data pulse */
        __delay_us(30);         
        if(Data_In & 1)  /* check whether data is 1 or 0 */    
            data = ((data<<1) | 1); 
        else
            data = (data<<1);  
        while(Data_In & 1);
    }
    return data;
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
    CCP1CON=0x0C;        /* set PWM mode and no decimal value for PWM */
    TMR2=0;

    init();
    T2CONbits.TMR2ON=1;  /* Turn ON Timer2 */

    blink_leds();
    while (1){        
        init_DHT11();
        DHT11_CheckResponse();
        __1 = DHT11_ReadData();  /* read Relative Humidity's integral value */
        __2 = DHT11_ReadData();   /* read Relative Humidity's decimal value */
        __3 = DHT11_ReadData();   /* read Temperature's integral value */
        temputure_val_dec = DHT11_ReadData();    /* read Relative Temperature's decimal value */
        checksum = DHT11_ReadData();     /* read 8-bit checksum value */

        /*
           if (checksum != (__1 + __2 + __3 + checksum))
           printf("ERRROR");
           */
        for(duty_cycle=1;duty_cycle<199;duty_cycle++)
        {
            CCPR1L = duty_cycle;   /* load duty cycle */
            __delay_ms(20);
        }
        __delay_ms(500);

        for(duty_cycle=199;duty_cycle>1;duty_cycle--)
        {
            CCPR1L = duty_cycle;   /* load duty cycle */
            __delay_ms(20);
        }
        __delay_ms(500);
        //        CLRWDT();
    }

}



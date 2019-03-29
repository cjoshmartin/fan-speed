#include "seven-segment.h"
#include "general.h"
#include <pic18f4331.h>
#include <xc.h>
#define DELAY_AMOUNT 100

void init_seven_segment(){
    /* 7- segment display */

    TRISAbits.RA0 = 0;
    TRISAbits.RA1 = 0;
    TRISAbits.RA2 = 0;
    TRISAbits.RA3 = 0;
    TRISAbits.RA4 = 0;
    TRISAbits.RA5 = 0;
    TRISEbits.RE0 = 0;
    TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA1 = 0;
    TRISAbits.TRISA2 = 0;
    TRISAbits.TRISA3 = 0;
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA5 = 0;
    TRISEbits.TRISE0 = 0;
}

void _clear_all(){
    PORTAbits.RA0 = 0;
    PORTAbits.RA1 = 0;
    PORTAbits.RA2 = 0;
    PORTEbits.RE0 = 0;
    PORTAbits.RA3 = 0;
    PORTAbits.RA4 = 0;
    PORTAbits.RA5 = 0;
}
void test_all(){

    _clear_all();
    PORTAbits.RA0 = 1;
    delay(DELAY_AMOUNT);
    _clear_all();
    PORTAbits.RA1 = 1;
    delay(DELAY_AMOUNT);
    _clear_all();
    PORTAbits.RA2 = 1;
    delay(DELAY_AMOUNT);
    _clear_all();
    PORTEbits.RE0 = 1;
    delay(DELAY_AMOUNT);
    _clear_all();
    PORTAbits.RA3 = 1;
    delay(DELAY_AMOUNT);
    _clear_all();
    PORTAbits.RA4 = 1;
    delay(DELAY_AMOUNT);
    _clear_all();
    PORTAbits.RA5 = 1;
    delay(DELAY_AMOUNT);

}
void emergency(int value){
    switch(value % 5){
        case 0:
    PORTAbits.RA2 = 1;
    break;
        case 1:
    PORTAbits.RA3 = 1;
    break;
        case 2:
    PORTAbits.RA4 = 1;
    break;
        case 3:
    PORTEbits.RE0 = 1;
    break;
        case 4:
    PORTAbits.RA5 = 1;
    break;
}
}

void one(int value){
    
    switch(value % 2){
        case 0:
    PORTAbits.RA0 = 1;
    break;
        case 1:
    PORTAbits.RA1 = 1;
    break;
}
}
void two(int value){
    switch (value % 5){
        case 0:
    PORTAbits.RA1 = 1;
    break;
        case 1:
    PORTAbits.RA2 = 1;
    break;
        case 2:
    PORTAbits.RA3 = 1;
    break;
        case 3:
    PORTAbits.RA4 = 1;
    break;
        case 4:
    PORTAbits.RA5 = 1;
    break;
}
}
void three(int value){
    switch(value % 5){
        case 0:
    PORTAbits.RA1 = 1;
    break;
        case 1:
    PORTAbits.RA2 = 1;
    break;
        case 2:
    PORTAbits.RA3 = 1;
    break;
        case 3:
    PORTAbits.RA0 = 1;
    break;
        case 4:
    PORTAbits.RA5 = 1;
    break;
   }
}
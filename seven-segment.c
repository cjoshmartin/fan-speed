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
void zero(){
    PORTAbits.RA0 = 1;
    PORTAbits.RA1 = 1;
    PORTAbits.RA2 = 1;
    PORTAbits.RA4 = 1;
    PORTEbits.RE0 = 1;
    PORTAbits.RA5 = 1;
}

void one(){
    PORTAbits.RA0 = 1;
    PORTAbits.RA1 = 1;
}
void two(){
    PORTAbits.RA1 = 1;
    PORTAbits.RA2 = 1;
    PORTAbits.RA3 = 1;
    PORTAbits.RA4 = 1;
    PORTAbits.RA5 = 1;
}
void three(){
    PORTAbits.RA1 = 1;
    PORTAbits.RA2 = 1;
    PORTAbits.RA3 = 1;
    PORTAbits.RA0 = 1;
    PORTAbits.RA5 = 1;
}
void four(){
    PORTAbits.RA1 = 1;
    PORTEbits.RE0 = 1;
    PORTAbits.RA3 = 1;
    PORTAbits.RA0 = 1;
}
void five(){
    PORTEbits.RE0 = 1;
    PORTAbits.RA2 = 1;
    PORTAbits.RA3 = 1;
    PORTAbits.RA0 = 1;
    PORTAbits.RA5 = 1;
}
void six(){
    PORTEbits.RE0 = 1;
    PORTAbits.RA2 = 1;
    PORTAbits.RA3 = 1;
    PORTAbits.RA0 = 1;
    PORTAbits.RA4 = 1;
    PORTAbits.RA5 = 1;
}
void seven(){
    PORTAbits.RA0 = 1;
    PORTAbits.RA1 = 1;
    PORTAbits.RA2 = 1;
}
void eight(){
    PORTAbits.RA0 = 1;
    PORTAbits.RA1 = 1;
    PORTAbits.RA2 = 1;
    PORTAbits.RA4 = 1;
    PORTEbits.RE0 = 1;
    PORTAbits.RA5 = 1;
    PORTAbits.RA3 = 1;
}
void nine(){
    PORTAbits.RA0 = 1;
    PORTAbits.RA1 = 1;
    PORTAbits.RA2 = 1;
    PORTEbits.RE0 = 1;
    PORTAbits.RA5 = 1;
    PORTAbits.RA3 = 1;
}
void display_number(int i){
    _clear_all();

    switch(i){
        case 0:
            zero();
            break;
        case 1:
            one();
            break;
        case 2:
            two();
            break;
        case 3:
            three();
            break;
        case 4:
            four();
            break;
        case 5: 
            five();
            break;
        case 6:
            six();
            break;
        case 7: 
            seven();
            break;
        case 8: 
            eight();
            break;
        case 9:
            nine();
            break;
    }

}

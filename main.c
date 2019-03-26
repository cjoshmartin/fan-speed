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

#include "leds.h"
        void init(){
          TRISBbits.RB0 = 0;
          TRISBbits.RB1 = 0;
          TRISBbits.RB2 = 0;
          TRISBbits.RB3 = 0;
          TRISBbits.TRISB0 = 0;
          TRISBbits.TRISB1 = 0;
          TRISBbits.TRISB2 = 0;
          TRISBbits.TRISB3 = 0;
       
       }                           
                /* ****************** MAIN ****************** */

      void main(void){
          init();
          blink_leds();
          while (1){
//              on_low();
              moving_leds();
          }
           
        }
        


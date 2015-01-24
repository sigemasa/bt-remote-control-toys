/* 
 * File:   main.c
 * Author: sigemasa
 *
 * Created on 2015/01/04, 11:52
 */

#define _XTAL_FREQ 4000000

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

#pragma config FOSC = INTOSCIO        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is digital input, MCLR internally tied to VDD)
#pragma config BOREN = OFF       // Brown-out Detect Enable bit (BOD enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

extern void ledblink(void );
extern void receive_main(void );
volatile unsigned char cnt;

int main(void) {

    PCON  = 0b00001000;
    PORTA = 0b00000000;
    CMCON = 0b00000111;
    TRISA = 0b00000000;

    receive_main();
    
    //TMR1?????????
    //250ms=0.125us(8MHz)*4*???????8*62500????
//    T1CON = 0b00111001; //???? ???Fosc/4, ???????8, TMR1ON
//    //TMR1??????? 62500?(????????)Max?65535?
//    TMR1H = (-62500 >> 8);
//    TMR1L = (-62500 & 0x00ff);
//    PIE1bits.TMR1IE = 1; //Timer1??????
//    INTCONbits.PEIE = 1; //????????????
//    ei();
//
//    cnt = 0; //4??????????
//    //cont ????????????????????????
//    while(1) {
//        if (cnt % 10 == 0) { //
//            PORTAbits.RA1 = 1;
//            cnt = 0;
//        }
//    }
}

/*
 * ????????
 */
//static void interrupt isr(void) {
//    if(PIR1bits.TMR1IF == 1) {  //?????Timer1??????
//        PIR1bits.TMR1IF = 0; //Timer1???????????
//        //TMR1??????? 62500?(????????)Max?65535?
//        TMR1H = (-62500 >> 8);
//        TMR1L = (-62500 & 0x00ff);
//
//        cnt++; //4?????? ???????
//    }
//}

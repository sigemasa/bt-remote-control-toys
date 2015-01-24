#define _XTAL_FREQ 4000000

#include <xc.h>

void device_init(void ) {
     CMCON  = 0b00000111 ;     // ????????????(RA0-RA4??????????)
     VRCON  = 0b00000000 ;     // RA2??????????
     PORTA  = 0 ;              // ??????????
     PORTB  = 0 ;              // ??????????
     TRISA  = 0b00100000 ;     // 1?INPUT 0?OUTPUT   RA5?INPUT Only
     TRISB  = 0b00000110 ;
     // UART settings
     TXSTA  = 0b00100100 ;
     // bit7 CSRC: Async: DontCare
     //            Sync : 1 -> Master Mode (Clock genareted internally from BRG)
     //                 : 0 -> Slave Mode (Clock from external source)
     // bit6 TX9: bit9 Transmit
     //         1 -> Select 9-bit transmission
     //         0 -> Select 8-bit transmission
     // bit5 TXEN: transmit Enable bit
     //         1 -> Tranmit enabled
     //         0 -> Transmit disabled
     // bit4 SYNC USART Mode Select bit
     //         1-> Sync mode
     //         0-> Async mode
     // bit3 not care
     // bit2 BRGH
     //     1-> High speed
     //     0-> Low  speed
     // bit1 TRMT Transmit Shift Register Status bit
     //     1-> TSR empty
     //     0-> TSR full
     // bit0 TX9D 9th bit of transmit data. Can be parity bit.
     RCSTA  = 0b10010000 ;    // ??????
     SPBRG  = 0x19 ;            // BRGH=1, 9600baud.
                              // 0x19 @ 4MHz Internal
                              // 129  @ 20MHz HS
     // To minimize power consumption.
//     T1CON = 0b00000100;
        //bit<7:6>: unused
        //bit<5:4>: T1CKPS Timer1 input clock prescale seelct bit
        // 11 = 1:8 Prescale value
        // 10 = 1:4 Prescale value
        // 01 = 1:2 Prescale value
        // 00 = 1:1 Prescale value
        //bit<3>: T1OSCEN Timer1 Oscillator Enable Control bit: <external crystal /or clock is required>
        // 1 = Oscillator is enabled
        // 0 = Oscillator is disabled
        // bit<2>:  ~T1SYNC  Timer1 External Clock Input Synchronization Control bit
        //     TMR1CS = 1
        //           1 = Do not synchronize external clock input
        //           0 = Synchronize external clock input
        //     TMR1CS = 0
        //           This bit is ignored. Timer1 uses the internal clock when TMR1CS = 0
        // bit<1>: TMR1CS Timer1 Clock Source Select bit
        //  1 = External clock from pin RB1/T1OSO/T1CKI/PGC(on the rising edge)
        //  0 = Internal clock (Fosc/4)
        // bit<0>: TMR1ON: Timer1 On bit
        //  1 = Enables Timer1
        //  0 = Stops Timer1

     // PWM setting
     // the following order of instructions should be taken
     // by data sheets.
     //PWM period is 1.22KHz
     CCP1M3 = 1;
     CCP1M2 = 1;
     CCP1M1 = 0;
     CCP1M0 = 0;
    PR2 = 0xff;
     // initial duty is 100%
    CCPR1L = 0x64;
    CCP1X = 0;
    CCP1Y = 0;
    TRISB3 = 0;
    T2CON = 0b01111111;
    //bit 7 Unimplemented: Read as ?0?
    //bit 6-3 TOUTPS<3:0>: Timer2 Output Postscale Select bits
    //0000 = 1:1 Postscale Value
    //0001 = 1:2 Postscale Value
    //...
    //...
    //...
    //1111 = 1:16 Postscale
    //bit 2 TMR2ON: Timer2 On bit
    //1 = Timer2 is on
    //0 = Timer2 is off
    //bit 1-0 T2CKPS<1:0>: Timer2 Clock Prescale Select bits
    //00 = 1:1 Prescaler Value
    //01 = 1:4 Prescaler Value
    //1x = 1:16 Prescaler Value

     // that all for initialize and begin handle interrupt.
     TXIE = 0;  // Transmit Interrupt is not used at this point.
     RCIE = 1 ;                // ????????????????
     PEIE = 1 ;                // ?????????????
     GIE  = 1 ;                // ???????????
}

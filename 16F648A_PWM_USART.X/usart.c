#define _XTAL_FREQ 4000000

#include <xc.h>
#include <string.h>

void device_init(void );
void ledblink(void );
void sendDataHandler(volatile unsigned char* ptr, const char* msg);

#define BUFFER_LENGTH 20

// Receive Buffer
volatile unsigned char RCV_Buff;
volatile unsigned char sendDataBuff[BUFFER_LENGTH];

// for send interrupt handle.
short i = 0;
volatile short sendDataLen = 0;

// DataArrival Flag 1:Receive 0:None
volatile int RxInd;
volatile int TxReq = 0;

void interrupt InterReceiver( void )
{
     if (RCIF && RCIE) {
          RCV_Buff = RCREG;
          RxInd = 1;
     }
     if (TXIF && TXIE) {
         if (sendDataLen == 0) {
             i = 0;
             TXIE = 0;
             return;
         }
         TXREG = sendDataBuff[i++];
         --sendDataLen;
     }
}

void receive_main()
{
    // initialize .device
    device_init();

    // Message string to Host console.
    const char *forward = "Forward\n";
    const char *backward = "Backward\n";
    const char *up = "Accelarate\n";
    const char *down = "Deaccelarate\n";
    const char *stop = "Cease\n";
    //const char *duty = "PWM duty ratio :";
    //const char *cycle= "PWM cycle value:";

     // Main loop
     while(1) {
        // form debug purpose
        // RB0 = 1;
        // __delay_ms(2000);
        // RB0 = 0;
        // __delay_ms(2000);
         
         if (RxInd == 1) {
             RxInd = 0 ;
             switch (RCV_Buff) {
                case 'F':
                    sendDataHandler(sendDataBuff, forward);
                    TXIE = 1;
                    RB0 = 0;
                    RB5 = 1;
                    break;
                case 'B':
                    sendDataHandler(sendDataBuff, backward);
                    TXIE = 1;
                    RB0 = 1;
                    RB5 = 0;
                    break;
                case 'A':
                    sendDataHandler(sendDataBuff, up);
                    TXIE = 1;
                    CCPR1L += 2;
                    break;
                case 'D':
                    sendDataHandler(sendDataBuff, down);
                    TXIE = 1;
                    CCPR1L -= 2;
                    break;
                case 'S': // 0x53
                    sendDataHandler(sendDataBuff, stop);
                    TXIE = 1;
                    RB0 = 1;
                    RB5 = 1;
                    __delay_ms(300);
                    RB0 = 0;
                    RB5 = 0;
                    break;
//                default: // 0x56 ?
//                    di();
//                    sendDataBuff[0] = RCV_Buff;
//                    sendDataLen = 1;
//                    ei();
//                    TXIE = 1;
//                    break;
             }
             
         }
     }
}

void sendDataHandler (volatile unsigned char* ptr, const char* msg) {
    if (sendDataLen == 0) {
        di();
        size_t SendDataBytes = strlen(msg);
        memcpy(ptr, msg, SendDataBytes);
        sendDataLen = SendDataBytes;
        ei();
    }
}

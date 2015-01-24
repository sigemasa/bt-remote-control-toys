#define _XTAL_FREQ 4000000

#include <xc.h>
extern void ledblink(void);

void ledblink(void )
{
  TRISB0 = 0; //RB0 as Output PIN
  while(1)
  {
    RB0 = 1;  // LED ON
    __delay_ms(5); // miliseconds
    RB0 = 0;  // LED OFF
    __delay_ms(5); // miliseconds
  }
}

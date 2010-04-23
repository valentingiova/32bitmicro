#include "LPC13xx.h"			/* LPC13xx Peripheral Registers */

extern void RC5_Init(void);

extern unsigned char RC5_flag;
extern unsigned char RC5_System;
extern unsigned char RC5_Command;

int main( void)
{
  SystemInit();
  
  RC5_Init();

  while (1)
  {
    if (RC5_flag)                      // wait for RC5 code
    {
      RC5_flag = 0;
/* FIXME */
/*  printf( "RC5 =  %d   %d\n", RC5_System, RC5_Command); */
    }
  }
}


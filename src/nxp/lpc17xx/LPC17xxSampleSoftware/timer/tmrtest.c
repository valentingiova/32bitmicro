/*****************************************************************************
 *   tmrtest.c:  main C entry file for NXP LPC17xx Family Microprocessors
 *
 *   Copyright(C) 2009, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.05.26  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#include <lpc17xx.h>
#include "type.h"
#include "timer.h"

extern uint32_t timer0_counter;

/*****************************************************************************
**   Main Function  main()
*****************************************************************************/
int main (void)
{	    		
  uint32_t counter = 0;
   SystemInit();
  /************ The main Function is an endless loop ************/
  
  GPIO2 -> FIODIR = 0x000000FF;		/* P1.16..23 defined as Outputs */
  GPIO2 -> FIOCLR = 0x000000FF;		/* turn off all the LEDs */
    
  init_timer( 0, TIME_INTERVAL ); // 10ms	
  enable_timer( 0 );

  while (1) 
  {					/* Loop forever */
	if ( timer0_counter >= (50 * counter) )	   // 0.5s
	{
	  GPIO2 -> FIOSET = 1 << counter;
	  counter++;
	  if ( counter > 8 )
	  {
		counter = 0;	
		timer0_counter = 0;
		GPIO2 -> FIOCLR = 0x000000FF;
	  }
	}
  }
}

/*****************************************************************************
**                            End Of File
******************************************************************************/

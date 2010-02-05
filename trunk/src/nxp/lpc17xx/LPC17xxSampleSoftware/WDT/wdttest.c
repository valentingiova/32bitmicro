/*****************************************************************************
 *   wdttest.c:  main C entry file for NXP LPC17xx Family Microprocessors
 *
 *   Copyright(C) 2009, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.05.27  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#include <lpc17xx.h>
#include "type.h"
#include "timer.h"
#include "wdt.h"

extern volatile uint32_t timer0_counter;
volatile uint32_t feed_counter = 0;

/*****************************************************************************
**   Main Function  main()
******************************************************************************/
int main (void)
{ 
	SystemInit();
		    		
  /*** The main Function is an endless loop ****/
  init_timer( 0, TIME_INTERVAL);
    
  WDTInit();
  enable_timer( 0 );

  while( 1 ) 
  {
	if ( timer0_counter > 0 )
	{
	  /* Feed the watchdog timer */
	  feed_counter++;
	  WDTFeed();
	  timer0_counter = 0;
	}
  }
}

/*********************************************************************************
**                            End Of File
*********************************************************************************/

/*****************************************************************************
 *   einttest.c:  main C entry file for NXP LPC17xx Family Microprocessors
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
#include "extint.h"

/*****************************************************************************
**   Main Function  main()
******************************************************************************/
int main (void)
{	    		
  /* initialize GPIO pins as external interrupts */
  SystemInit();        
  EINTInit();

  /****** It's an endless loop waiting for external interrupt ******/    
     
  while( 1 );
}

/******************************************************************************
**                            End Of File
******************************************************************************/

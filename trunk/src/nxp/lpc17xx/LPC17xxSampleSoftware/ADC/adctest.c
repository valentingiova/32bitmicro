/*****************************************************************************
 *   adctest.c:  main C entry file for NXP LPC17xx Family Microprocessors
 *
 *   Copyright(C) 2009, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.05.25  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#include <lpc17xx.h>
#include "type.h"
#include "adc.h"


extern volatile uint32_t ADC0Value[ADC_NUM];
extern volatile uint32_t ADC0IntDone;
extern void TargetResetInit(void);
/*****************************************************************************
**   Main Function  main()
******************************************************************************/
int main (void)
{
	uint32_t i;
  	SystemInit();
  /* Initialize ADC  */
	ADCInit( ADC_CLK );
	while(1)
	{
#if ADC_INTERRUPT_FLAG			/* Interrupt driven */
		for ( i = 0; i < ADC_NUM; i++ )
		{
			ADC0Read( i );
			while ( !ADC0IntDone );
			ADC0IntDone = 0;
		}
#else  					/* Polling */
		for ( i = 0; i < ADC_NUM; i++ )
		{
			ADC0Value[i] = ADC0Read( i );
		}
#endif
	}
}

/*****************************************************************************
**                            End Of File
*****************************************************************************/


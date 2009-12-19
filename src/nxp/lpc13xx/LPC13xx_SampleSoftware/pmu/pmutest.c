/*****************************************************************************
 *   pmutest.c:  main C entry file for NXP LPC13xx Family Microprocessors
 *
 *   Copyright(C) 2008, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2008.07.19  ver 1.00    Preliminary version, first Release
 *
******************************************************************************/
#include "LPC13xx.h"			/* LPC13xx Peripheral Registers */
#include "gpio.h"
#include "timer16.h"
#include "pmu.h"

extern volatile uint32_t timer16_0_counter;

/*****************************************************************************
**   Main Function  main()
******************************************************************************/
int main (void)
{
#if !TEST_POWERDOWN
  uint32_t regVal;
#endif

  SystemInit();

  /* Enable AHB clock to the GPIO domain. */
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);

#if !TEST_POWERDOWN
  /* Setup wakeup source before sleep or deep sleep. Current,
  port0.1 is configured as wakeup source, falling edge trigger. */    
  PMU_Init();
  /* Put X/Y/Z into sleep mode. */
  regVal = USB_PLL_PD|SYS_PLL_PD|WDT_OSC_PD|ADC_PD|BOD_PD;
  PMU_Sleep( 1, regVal );
#else
  /* Config PMU_PCON to let MCU to deep power down mode, retain 
  pattern in general-purpose register. A low on P1.4 will wake up
  the part from deep power down. */
  PMU_PowerDown();
#endif

  /* Using 16-bit timer 0 for LED blinky rate. */
  init_timer16(0, TIME_INTERVAL);
  enable_timer16(0);
  
  /* Set port 2_0 to output as LED control */
  GPIOSetDir( 2, 0, 1 );

  while (1)                                /* Loop forever */
  {
	/* I/O configuration and LED setting pending. */
	if ( (timer16_0_counter > 0) && (timer16_0_counter <= 200) )
	{
	  GPIOSetValue( 2, 0, 0 );
	}
	if ( (timer16_0_counter > 200) && (timer16_0_counter <= 400) )
	{
	  GPIOSetValue( 2, 0, 1 );
	}
	else if ( timer16_0_counter > 400 )
	{
	  timer16_0_counter = 0;
	}
  }
}

/*********************************************************************************
**                            End Of File
*********************************************************************************/

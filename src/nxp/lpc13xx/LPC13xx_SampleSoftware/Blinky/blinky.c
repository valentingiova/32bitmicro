/*****************************************************************************
 *   blinky.c:  LED blinky C file for NXP LPC13xx Family Microprocessors
 *
 *   Copyright(C) 2008, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2008.08.20  ver 1.00    Preliminary version, first Release
 *
******************************************************************************/


#include "LPC13xx.h"                        /* LPC13xx definitions */
#include "timer16.h"
#include "clkconfig.h"
#include "gpio.h"

#define TEST_TIMER_NUM		0		/* 0 or 1 for 16-bit timers only */

extern volatile uint32_t timer16_0_counter;
extern volatile uint32_t timer16_1_counter;

/* configuration for LPCXpresso board */

#define LED_PORT 0		// Port for led
#define LED_BIT 7		// Bit on port for led
#define LED_ON 1		// Level to set port to turn on led
#define LED_OFF 0		// Level to set port to turn off led
#define LED_TOGGLE_TICKS 100 // 100 ticks = 1 Hz flash rate

extern char _bss;
extern char _ebss;
/* Main Program */
void x_start() 
{
  char* r0 = &_bss;
  char* r1 = &_ebss;
  char  r2 =0;
  while(r0<r1) {
	*r0++ = r2;
 }
   main();
}

int main (void) {

/* Basic chip initialization is taken care of in SystemInit() called
   * from the startup code. SystemInit() and chip settings are defined
   * in the CMSIS system_<part family>.c file.
   */
/*  SystemInit(); */

  /* Config CLKOUT, mostly used for debugging. */
  CLKOUT_Setup( CLKOUTCLK_SRC_MAIN_CLK );
  LPC_IOCON->PIO0_1 &= ~0x07;	
  LPC_IOCON->PIO0_1 |= 0x01;		/* CLK OUT */

  /* Enable AHB clock to the GPIO domain. */
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);

  /* TEST_TIMER_NUM is either 0 or 1 for 16-bit timer 0 or 1. */
  init_timer16(TEST_TIMER_NUM, TIME_INTERVAL);
  enable_timer16(TEST_TIMER_NUM);

  /* Set port 2_0 to output */
/*  GPIOSetDir( 2, 0, 1 ); */
  /* Set LED port pin to output */
  GPIOSetDir( LED_PORT, LED_BIT, 1 );

  while (1)                                /* Loop forever */
  {
#if TEST_TIMER_NUM
	/* I/O configuration and LED setting pending. */
	if ( (timer16_1_counter > 0) && (timer16_1_counter <= 200) )
	{
	  /* GPIOSetValue( 2, 0, 0 ); */
	  GPIOSetValue( LED_PORT, LED_BIT, LED_OFF );
	}
	if ( (timer16_1_counter > 200) && (timer16_1_counter <= 400) )
	{
	  /* GPIOSetValue( 2, 0, 1 ); */
	  GPIOSetValue( LED_PORT, LED_BIT, LED_ON );
	}
	else if ( timer16_1_counter > 400 )
	{
	  timer16_1_counter = 0;
	}
#else
	/* I/O configuration and LED setting pending. */
	if ( (timer16_0_counter > 0) && (timer16_0_counter <= 200) )
	{
	  /* GPIOSetValue( 2, 0, 0 ); */
	  GPIOSetValue( LED_PORT, LED_BIT, LED_OFF );
	}
	if ( (timer16_0_counter > 200) && (timer16_0_counter <= 400) )
	{
	  /* GPIOSetValue( 2, 0, 1 ); */
	  GPIOSetValue( LED_PORT, LED_BIT, LED_ON );
	}
	else if ( timer16_0_counter > 400 )
	{
	  timer16_0_counter = 0;
	}
#endif
  }
}

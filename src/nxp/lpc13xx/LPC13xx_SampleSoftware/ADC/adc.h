/*****************************************************************************
 *   adc.h:  Header file for NXP LPC134x Family Microprocessors
 *
 *   Copyright(C) 2008, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2008.07.19  ver 1.00    Preliminary version, first Release
 *   2009.12.12  ver 1.01    Allow defines from Makefile
******************************************************************************/
#ifndef __ADC_H 
#define __ADC_H

#if !defined(ADC_INTERRUPT_FLAG)
#define ADC_INTERRUPT_FLAG		1	/* 1 is interrupt driven, 0 is polling */
#endif
#if !defined(BURST_MODE)
#define BURST_MODE			0	/* Burst mode works in interrupt driven mode only. */
#endif
#if !defined(ADC_DEBUG)
#define ADC_DEBUG			0
#endif

#define ADC_OFFSET		0x10
#define ADC_INDEX		4

#define ADC_DONE		0x80000000
#define ADC_OVERRUN		0x40000000
#define ADC_ADINT		0x00010000

#define ADC_NUM			8			/* for LPC13xx */
#define ADC_CLK			1000000		/* set to 1Mhz */

extern void ADC_IRQHandler( void );
extern void ADCInit( uint32_t ADC_Clk );
extern uint32_t ADCRead( uint8_t channelNum );
extern void ADCBurstRead( void );
#endif /* end __ADC_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/

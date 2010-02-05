/*****************************************************************************
 *   adc.c:  ADC module file for NXP LPC17xx Family Microprocessors
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

volatile uint32_t ADC0Value[ADC_NUM];
volatile uint32_t ADC0IntDone = 0;

#if ADC_INTERRUPT_FLAG
/******************************************************************************
** Function name:		ADC0Handler
**
** Descriptions:		ADC0 interrupt handler
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void ADC_IRQHandler (void)  
{
  uint32_t regVal;
  
  regVal = ADC -> ADSTAT;		/* Read ADC will clear the interrupt */
  if ( regVal & 0x0000FF00 )	/* check OVERRUN error first */
  {
	regVal = (regVal & 0x0000FF00) >> 0x08;
	/* if overrun, just read ADDR to clear */
	/* regVal variable has been reused. */
	switch ( regVal )
	{
	  case 0x01:
		regVal = ADC -> ADDR0;
	  break;
	  case 0x02:
		regVal = ADC -> ADDR1;
	  break;
	  case 0x04:
		regVal = ADC -> ADDR2;
	  break;
	  case 0x08:
		regVal = ADC -> ADDR3;
	  break;
	  case 0x10:
		regVal = ADC -> ADDR4;
	  break;
	  case 0x20:
		regVal = ADC -> ADDR5;
	  break;
	  case 0x40:
		regVal = ADC -> ADDR6;
	  break;
	  case 0x80:
		regVal = ADC -> ADDR7;
	  break;
	  default:
	  break;
	}
	return;
  }
    
  if ( regVal & ADC_ADINT )
  {
	switch ( regVal & 0xFF )	/* check DONE bit */
	{
	  case 0x01:
		ADC0Value[0] = ( ADC -> ADDR0 >> 4 ) & 0xFFF;
	  break;
	  case 0x02:
		ADC0Value[1] = ( ADC -> ADDR1 >> 4 ) & 0xFFF;
	  break;
	  case 0x04:
		ADC0Value[2] = ( ADC -> ADDR2 >> 4 ) & 0xFFF;
	  break;
	  case 0x08:
		ADC0Value[3] = ( ADC -> ADDR3 >> 4 ) & 0xFFF;
	  break;
	  case 0x10:
		ADC0Value[4] = ( ADC -> ADDR4 >> 4 ) & 0xFFF;
	  break;
	  case 0x20:
		ADC0Value[5] = ( ADC -> ADDR5 >> 4 ) & 0xFFF;
	  break;
	  case 0x40:
		ADC0Value[6] = ( ADC -> ADDR6 >> 4 ) & 0xFFF;
	  break;
	  case 0x80:
		ADC0Value[7] = ( ADC -> ADDR7 >> 4 ) & 0xFFF;
	  break;		
	  default:
	  break;
	}
  }
  ADC -> ADCR &= 0xF8FFFFFF;	/* stop ADC now */ 
  ADC0IntDone = 1;

}
#endif

/*****************************************************************************
** Function name:		ADCInit
**
** Descriptions:		initialize ADC channel
**
** parameters:			ADC clock rate
** Returned value:		true or false
** 
*****************************************************************************/
uint32_t ADCInit( uint32_t ADC_Clk )
{

  /* Enable CLOCK into ADC controller */
  SC -> PCONP |= (1 << 12);

  /* all the related pins are set to ADC inputs, AD0.0~7 */
  PINCON -> PINSEL0 |= 0x0F000000;	/* P0.12~13, A0.6~7, function 11 */	
  PINCON -> PINSEL1 &= ~0x003FC000;	/* P0.23~26, A0.0~3, function 01 */
  PINCON -> PINSEL1 |= 0x00154000;
  PINCON -> PINSEL3 |= 0xF0000000;	/* P1.30~31, A0.4~5, function 11 */

  ADC -> ADCR = ( 0x01 << 0 ) | 	/* SEL=1,select channel 0 on ADC0 */
		( ( 18000000 / ADC_Clk - 1 ) << 8 ) |  /* CLKDIV = Fpclk / ADC_Clk - 1 */ 
		( 0 << 16 ) | 		/* BURST = 0, no BURST, software controlled */
		( 0 << 17 ) |  		/* CLKS = 0, 11 clocks/10 bits */
		( 1 << 21 ) |  		/* PDN = 1, normal operation */
		( 0 << 24 ) |  		/* START = 0 A/D conversion stops */
		( 0 << 27 );		/* EDGE = 0 (CAP/MAT singal falling,trigger A/D conversion) */ 

  /* If POLLING, no need to do the following */
#if ADC_INTERRUPT_FLAG
  ADC -> ADINTEN = 0x1FF;		/* Enable all interrupts */

	NVIC_EnableIRQ(ADC_IRQn);

#endif
  return (TRUE);
}

/*****************************************************************************
** Function name:		ADC0Read
**
** Descriptions:		Read ADC0 channel
**
** parameters:			Channel number
** Returned value:		Value read, if interrupt driven, return channel #
** 
*****************************************************************************/
uint32_t ADC0Read( uint8_t channelNum )
{
#if !ADC_INTERRUPT_FLAG
  uint32_t regVal, ADC_Data;
#endif

  /* channel number is 0 through 7 */
  if ( channelNum >= ADC_NUM )
  {
	channelNum = 0;		/* reset channel number to 0 */
  }
  ADC -> ADCR &= 0xFFFFFF00;
  ADC -> ADCR |= (1 << 24) | (1 << channelNum);	
				/* switch channel,start A/D convert */
#if !ADC_INTERRUPT_FLAG
  while ( 1 )			/* wait until end of A/D convert */
  {
	regVal = *(volatile unsigned long *)(ADC_BASE 
			+ ADC_OFFSET + ADC_INDEX * channelNum);
	/* read result of A/D conversion */
	if ( regVal & ADC_DONE )
	{
	  break;
	}
  }	
        
  ADC -> ADCR &= 0xF8FFFFFF;	/* stop ADC now */    
  if ( regVal & ADC_OVERRUN )	/* save data when it's not overrun, otherwise, return zero */
  {
	return ( 0 );
  }
  ADC_Data = ( regVal >> 4 ) & 0xFFF;
  return ( ADC_Data );	/* return A/D conversion value */
#else
  return ( channelNum );	/* if it's interrupt driven, the ADC reading is 
							done inside the handler. so, return channel number */
#endif
}

/*********************************************************************************
**                            End Of File
*********************************************************************************/

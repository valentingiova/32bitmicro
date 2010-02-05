/*****************************************************************************
 *   dma.c:  DMA module file for NXP LPC17xx Family Microprocessors
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
#include "dma.h"

volatile uint32_t DMATCCount = 0;
volatile uint32_t DMAErrCount = 0;

/******************************************************************************
** Function name:		DMAHandler
**
** Descriptions:		DMA interrupt handler
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void DMA_IRQHandler (void) 
{
  uint32_t regVal;

  regVal = GPDMA -> DMACIntTCStat;
  if ( regVal )
  {
	DMATCCount++;
	GPDMA -> DMACIntTCClear |= regVal;
  } 

  regVal = GPDMA -> DMACIntErrStat;
  if ( regVal )
  {
	DMAErrCount++;
	GPDMA -> DMACIntErrClr |= regVal;
  } 

}

/******************************************************************************
** Function name:		DMA_Init
**
** Descriptions:		
**
** parameters:			
** Returned value:		
** 
******************************************************************************/
uint32_t DMA_Init( uint32_t DMAMode )
{

  SC -> PCONP |= (1 << 29);	/* Enable GPDMA clock */

  /* clear all interrupts on channel 0 */
  GPDMA -> DMACIntTCClear = 0x01;
  GPDMA -> DMACIntErrClr = 0x01;
   
  if ( DMAMode == M2M )
  {
	/* Ch0 is used for M2M test, for M2P and P2M, go to peripheral directories
	where both DAM and non DMA examples are provided. */
	GPDMACH0 -> DMACCSrcAddr = DMA_SRC;
	GPDMACH0 -> DMACCDestAddr = DMA_DST;
	/* Terminal Count Int enable */
	GPDMACH0 -> DMACCControl = ((DMA_SIZE/4) & 0x0FFF) | (0x04 << 12) | (0x04 << 15) 
		| (0x02 << 18) | (0x02 << 21) | (1 << 26) | (1 << 27) | 0x80000000;	
  }
  else
  {
	return ( FALSE );
  }
	
  GPDMA -> DMACConfig = 0x01;	/* Enable DMA channels, little endian */
  while ( !(GPDMA -> DMACConfig & 0x01) );    

	NVIC_EnableIRQ(DMA_IRQn);

  return (TRUE);
}

/******************************************************************************
**                            End Of File
******************************************************************************/

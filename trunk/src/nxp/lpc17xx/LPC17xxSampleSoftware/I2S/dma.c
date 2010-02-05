/*****************************************************************************
 *   dma.c:  DMA module file for NXP LPC17xx Family Microprocessors
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
#include "i2s.h"
#include "dma.h"

#if I2S_DMA_ENABLED
volatile uint32_t DMATCCount = 0;
volatile uint32_t DMAErrCount = 0;
volatile uint32_t I2SDMA0Done = 0;
volatile uint32_t I2SDMA1Done = 0;

/******************************************************************************
** Function name:		DMAHandler
**
** Descriptions:		DMA interrupt handler
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void DMA_IRQHandler(void) 
{
  uint32_t regVal;

  regVal = GPDMA -> DMACIntTCStat;
  if ( regVal )
  {
	DMATCCount++;
	GPDMA -> DMACIntTCClear |= regVal;
	if ( regVal & 0x01 )
	{
	  I2SDMA0Done = 1;
	}
	else if ( regVal & 0x02 )
	{
	  I2SDMA1Done = 1;
	}
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
uint32_t DMA_Init( uint32_t ChannelNum, uint32_t DMAMode )
{
  if ( ChannelNum == 0 )
  {
	GPDMA -> DMACIntTCClear = 0x01;   
	if ( DMAMode == M2P )
	{
	  /* Ch0 set for M2P transfer from mempry to I2S TX FIFO. */
	  GPDMACH0 -> DMACCSrcAddr = DMA_SRC;
	  GPDMACH0 -> DMACCDestAddr = DMA_I2S_TX_FIFO;
	  /* The burst size is set to 1. Terminal Count Int enable */
	  GPDMACH0 -> DMACCControl = (DMA_SIZE & 0x0FFF) | (0x00 << 12) | (0x00 << 15)
		| (1 << 26) | 0x80000000;
	}
	else if ( DMAMode == P2M )
	{
	  /* Ch0 set for P2M transfer from I2S RX FIFO to memory. */
	  GPDMACH0 -> DMACCSrcAddr = DMA_I2S_RX_FIFO;
	  GPDMACH0 -> DMACCDestAddr = DMA_DST;
	  /* The burst size is set to 1. Terminal Count Int enable. */
	  GPDMACH0 -> DMACCControl = (DMA_SIZE & 0x0FFF) | (0x00 << 12) | (0x00 << 15)
		| (1 << 27) | 0x80000000;
	}
	else if ( DMAMode == P2P )
	{
	  /* Ch0 set for P2P transfer from I2S DAO to I2S DAI. */
	  GPDMACH0 -> DMACCSrcAddr = DMA_I2S_TX_FIFO;
	  GPDMACH0 -> DMACCDestAddr = DMA_I2S_RX_FIFO;
	  /* The burst size is set to 32. */
	  GPDMACH0 -> DMACCControl = (DMA_SIZE & 0x0FFF) | (0x04 << 12) | (0x04 << 15) 
		| 0x80000000;
	}
	else
	{
	  return ( FALSE );
	}
  }
  else if ( ChannelNum == 1 )
  {   
	GPDMA -> DMACIntTCClear = 0x02;
	if ( DMAMode == M2P )
	{
	  /* Ch1 set for M2P transfer from mempry to I2S TX FIFO. */
	  GPDMACH1 -> DMACCSrcAddr = DMA_SRC;
	  GPDMACH1 -> DMACCDestAddr = DMA_I2S_TX_FIFO;
	  /* The burst size is set to 1. Terminal Count Int enable. */
	  GPDMACH1 -> DMACCControl = (DMA_SIZE & 0x0FFF) | (0x00 << 12) | (0x00 << 15)
		| (1 << 26) | 0x80000000;
	}
	else if ( DMAMode == P2M )
	{
	  /* Ch1 set for P2M transfer from I2S RX FIFO to memory. */
	  GPDMACH1 -> DMACCSrcAddr = DMA_I2S_RX_FIFO;
	  GPDMACH1 -> DMACCDestAddr = DMA_DST;
	  /* The burst size is set to 1. Terminal Count Int enable. */
	  GPDMACH1 -> DMACCControl = (DMA_SIZE & 0x0FFF) | (0x00 << 12) | (0x00 << 15)
		| (1 << 27) | 0x80000000;
	}
	else if ( DMAMode == P2P )
	{
	  /* Ch1 set for P2P transfer from I2S DAO to I2S DAI. */
	  GPDMACH1 -> DMACCSrcAddr = DMA_I2S_TX_FIFO;
	  GPDMACH1 -> DMACCDestAddr = DMA_I2S_RX_FIFO;
	  /* The burst size is set to 32. */
	  GPDMACH1 -> DMACCControl = (DMA_SIZE & 0x0FFF) | (0x04 << 12) | (0x04 << 15) 
		| 0x80000000;
	}
	else
	{
	  return ( FALSE );
	}
  }
  else
  {
	return ( FALSE );
  }
  return( TRUE );
}

#endif	/* end if DMA_ENABLED */

/******************************************************************************
**                            End Of File
******************************************************************************/

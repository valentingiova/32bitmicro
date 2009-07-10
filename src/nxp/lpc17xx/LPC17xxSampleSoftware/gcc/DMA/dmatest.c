/*****************************************************************************
 *   dmatest.c:  main C entry file for NXP LPC17xx Family Microprocessors
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

extern volatile uint32_t DMATCCount;

/******************************************************************************
**   Main Function  main()
******************************************************************************/
int main (void)
{	
  uint32_t i;
  uint32_t *src_addr, *dest_addr;
  SystemInit();    
  src_addr = (uint32_t *)DMA_SRC;
  dest_addr = (uint32_t *)DMA_DST;
  for ( i = 0; i < DMA_SIZE/4; i++ )
  {
	*src_addr++ = i;
	*dest_addr++ = 0;
  }
	    
  DMA_Init( M2M );
  GPDMACH0 -> DMACCConfig |= 0x08001;	/* Enable channel and IE bit */

  while ( !DMATCCount );		/* Wait until DMA is done */

  /* Verify result */
  src_addr = (uint32_t *)DMA_SRC;
  dest_addr = (uint32_t *)DMA_DST;
  for ( i = 0; i < DMA_SIZE/4; i++ )
  {
	if ( *src_addr++ != *dest_addr++ )
	{
	  while ( 1 );	/* fatal error */
	}
  }
  while(1);
}

/******************************************************************************
**                            End Of File
******************************************************************************/

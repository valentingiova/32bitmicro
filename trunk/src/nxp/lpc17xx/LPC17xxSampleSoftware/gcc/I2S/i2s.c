/*****************************************************************************
 *   i2s.c:  I2S C file for NXP LPC17xx Family Microprocessors
 *
 *   Copyright(C) 2009, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.05.26  ver 1.00    Prelimnary version, first Release
 *
*****************************************************************************/
#include <lpc17xx.h>
#include "type.h"
#include "i2s.h"
#include "dma.h"

/* treat I2S TX and RX as a constant address, make the code and buffer 
easier for both DMA and non-DMA test */
volatile uint8_t *I2STXBuffer = (uint8_t *)(DMA_SRC); 
volatile uint8_t *I2SRXBuffer = (uint8_t *)(DMA_DST);
volatile uint32_t I2SReadLength = 0;
volatile uint32_t I2SWriteLength = 0;
volatile uint32_t I2SRXDone = 0, I2STXDone = 0;

/*****************************************************************************
** Function name:		I2SHandler
**
** Descriptions:		I2S interrupt handler, only RX interrupt is enabled
**						for simplicity.
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void I2S_IRQHandler (void)  
{
  uint32_t RxCount = 0;

  if ( I2S -> I2SSTATE & 0x01 )
  {
	RxCount = (I2S -> I2SSTATE >> 8) & 0xFF;
	if ( (RxCount != RXFIFO_EMPTY) && !I2SRXDone )
	{
	  while ( RxCount > 0 )
	  {
		if ( I2SReadLength == BUFSIZE )
		{
		  /* Stop RX channel */

		  /* Note: if the version of the head file for 17xx is 1.0(21. Nov. 2008),
		           there should be an error[error #137:expression must be a 
				   modifiable lvalue keil] when you compile the project. Please 
				   modify the definition of I2SDAI in the head file like below:
				   __I  uint32_t I2SDAI; ----> __IO  uint32_t I2SDAI;
				   because this is a R/W register, not noly read. 
				   George Yan 2009.5.26      */

		  I2S -> I2SDAI |= ((0x01 << 3) | (0x01 << 4));
		  I2S -> I2SIRQ &= ~(0x01 << 0);	/* Disable RX */	
		  I2SRXDone = 1;
		  break;
		}
		else
		{
		  I2SRXBuffer[I2SReadLength++] = I2S -> I2SRXFIFO;
		}
		RxCount--;
	  }
	}
  }

}

/*****************************************************************************
** Function name:		I2SStart
**
** Descriptions:		Start I2S DAI and DAO
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void I2SStart( void )
{
  uint32_t DAIValue, DAOValue;
  
  /* Audio output is the master, audio input is the slave, */
  /* 16 bit data, stereo, reset, master mode, not mute. */
  DAOValue = I2S -> I2SDAO;
  DAIValue = I2S -> I2SDAI;
  I2S -> I2SDAO = DAOValue & (~((0x01 << 4)|(0x01 <<3)));
  /* 16 bit data, stereo, reset, slave mode, not mute. */
  I2S -> I2SDAI	= DAIValue & (~((0x01 << 4)|(0x01 <<3)));
  return;
}

/*****************************************************************************
** Function name:		I2SStop
**
** Descriptions:		Stop I2S DAI and DAO
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void I2SStop( void )
{
  uint32_t DAIValue, DAOValue;

  /* Stop the I2S to start. Audio output is master, audio input is the slave. */
  /* 16 bit data, set STOP and RESET bits to reset the channels */
  DAOValue = I2S -> I2SDAO;
  /* Switch to master mode, TX channel, no mute */
  DAOValue &= ~((0x01 << 5)|(0x01 << 15));
  DAIValue = I2S -> I2SDAI;
  DAIValue &= ~(0x01 << 15);
  I2S -> I2SDAO = (0x01 << 4) | (0x01 << 3) | DAOValue;	/* Master */
  I2S -> I2SDAI = (0x01 << 4) | (0x01 << 3) | DAIValue;	/* Slave */
  return;
}

/*****************************************************************************
** Function name:		I2SInit
**
** Descriptions:		Initialize I2S controller
**
** parameters:			None
** Returned value:		true or false, return false if the I2S
**						interrupt handler was not installed correctly
** 
*****************************************************************************/
uint32_t I2SInit( void ) 
{

  /*enable I2S in the PCONP register. I2S is disabled on reset*/
  SC -> PCONP |= (1 << 27);

  /*connect the I2S sigals to port pins(P0.4-P0.9)*/
  PINCON -> PINSEL0 &= ~0x000FFF00;
  PINCON -> PINSEL0 |= 0x00055500;

  /* Please note, in order to generate accurate TX/RX clock rate for I2S, 
  PCLK and CCLK needs to be carefully reconsidered. For this test 
  program, the TX is looped back to RX without external I2S device, 
  clock rate is not critical in this matter. */
  I2S -> I2STXRATE = 0x241;
  I2S -> I2SRXRATE = 0x241;

  I2SStop();

	NVIC_EnableIRQ(I2S_IRQn);

  return( TRUE );
}

/******************************************************************************
**                            End Of File
******************************************************************************/


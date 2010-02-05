/*****************************************************************************
 *   dma.h:  Header file for NXP LPC17xx Family Microprocessors
 *
 *   Copyright(C) 2009, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.05.25  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#ifndef __DMA_H 
#define __DMA_H

#define DMA_SRC			0x10004000
#define DMA_DST			0x10005000
#define DMA_SIZE		0x1000

#define M2M				0x00
#define M2P				0x01
#define P2M				0x02
#define P2P				0x03

extern void DMA_IRQHandler (void);
extern uint32_t DMA_Init( uint32_t DMAMode );

#endif /* end __DMA_H */
/****************************************************************************
**                            End Of File
****************************************************************************/

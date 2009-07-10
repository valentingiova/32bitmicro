/*****************************************************************************
 *  can.c:  CAN module API file for NXP LPC17xx Family Microprocessors
 *
 *   Copyright(C) 2009, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.05.27  ver 1.00    Prelimnary version, first Release
 *
*****************************************************************************/
#include <lpc17xx.h>
#include "type.h"
#include "can.h"

// Receive Queue: one queue for each CAN port
extern CAN_MSG MsgBuf_RX1, MsgBuf_RX2;
extern volatile uint32_t CAN1RxDone, CAN2RxDone;

volatile uint32_t CANStatus;
uint32_t CAN1RxCount = 0, CAN2RxCount = 0;
uint32_t CAN1ErrCount = 0, CAN2ErrCount = 0;

/******************************************************************************
** Function name:		CAN_ISR_Rx1
**
** Descriptions:		CAN Rx1 interrupt handler
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void CAN_ISR_Rx1( void )
{
  uint32_t * pDest;

  // initialize destination pointer
  pDest = (uint32_t *)&MsgBuf_RX1;
  *pDest = CAN1 -> RFS;  // Frame

  pDest++;
  *pDest = CAN1 -> RID; // ID		//change by gongjun

  pDest++;
  *pDest = CAN1 -> RDA; // Data A

  pDest++;
  *pDest = CAN1 -> RDB; // Data B
	
  CAN1RxDone = TRUE;
  CAN1 -> CMR = 0x04; // release receive buffer
  return;
}

/******************************************************************************
** Function name:		CAN_ISR_Rx2
**
** Descriptions:		CAN Rx2 interrupt handler
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void CAN_ISR_Rx2( void )
{
  uint32_t *pDest;

  // initialize destination pointer
  pDest = (uint32_t *)&MsgBuf_RX2;
  *pDest = CAN2 -> RFS;  // Frame

  pDest++;
  *pDest = CAN2 -> RID; // ID

  pDest++;
  *pDest = CAN2 -> RDA; // Data A

  pDest++;
  *pDest = CAN2 -> RDB; // Data B

  CAN2RxDone = TRUE;
  CAN2 -> CMR = 0x04; // release receive buffer
  return;
}

/*****************************************************************************
** Function name:		CAN_Handler
**
** Descriptions:		CAN interrupt handler
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void CAN_IRQHandler(void)  
{		

  CANStatus = CANCR -> CANRxSR;
  if ( CANStatus & (1 << 8) )
  {
	CAN1RxCount++;
	CAN_ISR_Rx1();
  }
  if ( CANStatus & (1 << 9) )
  {
	CAN2RxCount++;
	CAN_ISR_Rx2();
  }
  if ( CAN1 -> GSR & (1 << 6 ) )
  {
	/* The error count includes both TX and RX */
	CAN1ErrCount = (CAN1 -> GSR >> 16 );
  }
  if ( CAN2 -> GSR & (1 << 6 ) )
  {
	/* The error count includes both TX and RX */
	CAN2ErrCount = (CAN2 -> GSR >> 16 );
  }

  return;
}

/******************************************************************************
** Function name:		CAN_Init
**
** Descriptions:		Initialize CAN, install CAN interrupt handler
**
** parameters:			bitrate
** Returned value:		true or false, false if initialization failed.
** 
******************************************************************************/
uint32_t CAN_Init( uint32_t can_btr )
{

  CAN1RxDone = CAN2RxDone = FALSE;

  SC -> PCONP |= (1 << 13) | (1 << 14);	// Enable clock to the peripheral


	PINCON -> PINSEL0	&= 0xFFFFF0FF;	// ysq
	PINCON -> PINSEL0 |= 0x00000A00;	//	ysq

	PINCON -> PINSEL1 |= 0x00003C00;	// ysq

  CAN1 -> MOD = CAN2 -> MOD = 1;	// Reset CAN
  CAN1 -> IER = CAN2 -> IER = 0;	// Disable Receive Interrupt
  CAN1 -> GSR = CAN2 -> GSR = 0;	// Reset error counter when CANxMOD is in reset

  CAN1 -> BTR = CAN2 -> BTR = can_btr;
  CAN1 -> MOD = CAN2 -> MOD = 0x0;	// CAN in normal operation mode

	NVIC_EnableIRQ(CAN_IRQn);

  CAN1 -> IER = CAN2 -> IER = 0x01;		// Enable receive interrupts
  return( TRUE );
}

/******************************************************************************
** Function name:		CAN_SetACCF_Lookup
**
** Descriptions:		Initialize CAN, install CAN interrupt handler
**
** parameters:			bitrate
** Returned value:		true or false, false if initialization failed.
** 
******************************************************************************/
void CAN_SetACCF_Lookup( void )
{
  uint32_t address = 0;
  uint32_t i;
  uint32_t ID_high, ID_low;

  // Set explicit standard Frame  
  CANAF -> SFF_sa = address;
  for ( i = 0; i < ACCF_IDEN_NUM; i += 2 )
  {
	ID_low = (i << 29) | (EXP_STD_ID << 16);
	ID_high = ((i+1) << 13) | (EXP_STD_ID << 0);
	*((volatile uint32_t *)(CAN_MEM_BASE + address)) = ID_low | ID_high;
	address += 4; 
  }
		
  // Set group standard Frame 
  CANAF -> SFF_GRP_sa = address;
  for ( i = 0; i < ACCF_IDEN_NUM; i += 2 )
  {
	ID_low = (i << 29) | (GRP_STD_ID << 16);
	ID_high = ((i+1) << 13) | (GRP_STD_ID << 0);
	*((volatile uint32_t *)(CAN_MEM_BASE + address)) = ID_low | ID_high;
	address += 4; 
  }
 
  // Set explicit extended Frame 
  CANAF -> EFF_sa = address;
  for ( i = 0; i < ACCF_IDEN_NUM; i++  )
  {
	ID_low = (i << 29) | (EXP_EXT_ID << 0);
	*((volatile uint32_t *)(CAN_MEM_BASE + address)) = ID_low;
	address += 4; 
  }

  // Set group extended Frame 
  CANAF -> EFF_GRP_sa = address;
  for ( i = 0; i < ACCF_IDEN_NUM; i++  )
  {
	ID_low = (i << 29) | (GRP_EXT_ID << 0);
	*((volatile uint32_t *)(CAN_MEM_BASE + address)) = ID_low;
	address += 4; 
  }
   
  // Set End of Table 
  CANAF -> ENDofTable = address;
  return;
}

/******************************************************************************
** Function name:		CAN_SetACCF
**
** Descriptions:		Set acceptance filter and SRAM associated with	
**
** parameters:			ACMF mode
** Returned value:		None
**
** 
******************************************************************************/
void CAN_SetACCF( uint32_t ACCFMode )
{
  switch ( ACCFMode )
  {
	case ACCF_OFF:
	  CANAF -> AFMR = ACCFMode;
	  CAN1 -> MOD = CAN2 -> MOD = 1;	// Reset CAN
	  CAN1 -> IER = CAN2 -> IER = 0;	// Disable Receive Interrupt
	  CAN1 -> GSR = CAN2 -> GSR = 0;	// Reset error counter when CANxMOD is in reset
	break;

	case ACCF_BYPASS:
	  CANAF -> AFMR = ACCFMode;
	break;

	case ACCF_ON:
	case ACCF_FULLCAN:
	  CANAF -> AFMR = ACCF_OFF;
	  CAN_SetACCF_Lookup();
	  CANAF -> AFMR = ACCFMode;
	break;

	default:
	break;
  }
  return;
}

/******************************************************************************
** Function name:		CAN1_SendMessage
**
** Descriptions:		Send message block to CAN1	
**
** parameters:			pointer to the CAN message
** Returned value:		true or false, if message buffer is available,
**						message can be sent successfully, return TRUE,
**						otherwise, return FALSE.
** 
******************************************************************************/
uint32_t CAN1_SendMessage( CAN_MSG *pTxBuf )
{
  uint32_t CANStatus;

  CANStatus = CAN1 -> SR;
  if ( CANStatus & 0x00000004 )
  {
	CAN1 -> TFI1 = pTxBuf->Frame & 0xC00F0000;
	CAN1 -> TID1 = pTxBuf->MsgID;
	CAN1 -> TDA1 = pTxBuf->DataA;
	CAN1 -> TDB1 = pTxBuf->DataB;
	CAN1 -> CMR = 0x21;
	return ( TRUE );
  }
  else if ( CANStatus & 0x00000400 )
  {
	CAN1 -> TFI2 = pTxBuf->Frame & 0xC00F0000;
	CAN1 -> TID2 = pTxBuf->MsgID;
	CAN1 -> TDA2 = pTxBuf->DataA;
	CAN1 -> TDB2 = pTxBuf->DataB;
	CAN1 -> CMR = 0x41;
	return ( TRUE );
  }
  else if ( CANStatus & 0x00040000 )
  {	
	CAN1 -> TFI3 = pTxBuf->Frame & 0xC00F0000;
	CAN1 -> TID3 = pTxBuf->MsgID;
	CAN1 -> TDA3 = pTxBuf->DataA;
	CAN1 -> TDB3 = pTxBuf->DataB;
	CAN1 -> CMR = 0x81;
	return ( TRUE );
  }
  return ( FALSE );
}

/******************************************************************************
**                            End Of File
******************************************************************************/

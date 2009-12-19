/*****************************************************************************
 *   autousb.c: USB ISP for NXP LPC13xx Family Microprocessors
 *
 *   Copyright(C) 2009, 32bitmicro
 *   All rights reserved.
 *
 *   History
 *   2009.12.14  ver 1.00    Preliminary version, first Release
 *
******************************************************************************/
#include "LPC13xx.h"
#include "type.h"

#include "usb.h"
#include "usbcfg.h"
#include "usbhw.h"
#include "usbcore.h"
#include "cdc.h"
#include "cdcuser.h"
#include "serial.h"
#include "uart.h"

extern volatile uint32_t UARTCount;
extern volatile uint8_t UARTBuffer[BUFSIZE];

#define     EN_TIMER32_1    (1<<10)
#define     EN_IOCON        (1<<16)
#define     EN_USBREG       (1<<14)

/*----------------------------------------------------------------------------
 Initializes the VCOM port.
 Call this function before using VCOM_putchar or VCOM_getchar
 *---------------------------------------------------------------------------*/
void VCOM_Init(void) {

  CDC_Init ();
}


/*----------------------------------------------------------------------------
  Reads character from serial port buffer and writes to USB buffer
 *---------------------------------------------------------------------------*/
void VCOM_Serial2Usb(void) {
  static char serBuf [USB_CDC_BUFSIZE];
         int  numBytesRead, numAvailByte;
	
  ser_AvailChar (&numAvailByte);
  if (numAvailByte > 0) {
    if (CDC_DepInEmpty) {
      numBytesRead = ser_Read (&serBuf[0], &numAvailByte);

      CDC_DepInEmpty = 0;
	  USB_WriteEP (CDC_DEP_IN, (unsigned char *)&serBuf[0], numBytesRead);
    }
  }

}

/*----------------------------------------------------------------------------
  Reads character from USB buffer and writes to serial port buffer
 *---------------------------------------------------------------------------*/
void VCOM_Usb2Serial(void) {
  static char serBuf [32];
         int  numBytesToRead, numBytesRead, numAvailByte;

  CDC_OutBufAvailChar (&numAvailByte);
  if (numAvailByte > 0) {
      numBytesToRead = numAvailByte > 32 ? 32 : numAvailByte; 
      numBytesRead = CDC_RdOutBuf (&serBuf[0], &numBytesToRead);
      ser_Write (&serBuf[0], &numBytesRead);    
  }

}


/*----------------------------------------------------------------------------
  checks the serial state and initiates notification
 *---------------------------------------------------------------------------*/
void VCOM_CheckSerialState (void) {
         unsigned short temp;
  static unsigned short serialState;

  temp = CDC_GetSerialState();
  if (serialState != temp) {
     serialState = temp;
     CDC_NotificationIn();                  // send SERIAL_STATE notification
  }
}

/*----------------------------------------------------------------------------
  Main Program
 *---------------------------------------------------------------------------*/
int main (void) {
	  /* Basic chip initialization is taken care of in SystemInit() called
	   * from the startup code. SystemInit() and chip settings are defined
	   * in the CMSIS system_<part family>.c file.
	   */

	/* Enable Timer32_1, IOCON, and USB blocks */
	LPC_SYSCON->SYSAHBCLKCTRL |= (EN_TIMER32_1 | EN_IOCON | EN_USBREG);

  USBIOClkConfig();

  VCOM_Init();                              // VCOM Initialization

  USB_Init();                               // USB Initialization
  USB_Connect(TRUE);                        // USB Connect

  while (!USB_Configuration) ;              // wait until USB is configured

  while (1) {                               // Loop forever
    VCOM_Serial2Usb();                      // read serial port and initiate USB event
    VCOM_CheckSerialState();
	VCOM_Usb2Serial();
  } // end while											   
} // end main ()



#if 0 
// old
int main (void) {

  SystemInit();

  /* NVIC is installed inside UARTInit file. */
  UARTInit(115200);

  while (1) 
  {				/* Loop forever */
	if ( UARTCount != 0 )
	{
	  LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
	  UARTSend( (uint8_t *)UARTBuffer, UARTCount );
	  UARTCount = 0;
	  LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;	/* Re-enable RBR */
	}
  }
}

#endif

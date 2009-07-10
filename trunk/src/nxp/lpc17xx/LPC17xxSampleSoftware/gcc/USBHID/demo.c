/*----------------------------------------------------------------------------
 *      Name:    DEMO.C
 *      Purpose: USB HID Demo
 *      Version: V1.10
 *----------------------------------------------------------------------------
 *      This software is supplied "AS IS" without any warranties, express,
 *      implied or statutory, including but not limited to the implied
 *      warranties of fitness for purpose, satisfactory quality and
 *      noninfringement. Keil extends you a royalty-free right to reproduce
 *      and distribute executable files created using this software for use
 *      on NXP Semiconductors LPC family microcontroller devices only. Nothing 
 *      else gives you the right to use this software.
 *
 *      Copyright (c) 2005-2009 Keil Software.
 *---------------------------------------------------------------------------*/

#include <LPC17xx.H>                        /* LPC17xx definitions */

#include "type.h"

#include "usb.h"
#include "usbcfg.h"
#include "usbhw.h"

#include "demo.h"



uint8_t InReport;                              /* HID Input Report    */
                                            /*   Bit0   : Buttons  */
                                            /*   Bit1..7: Reserved */

uint8_t OutReport;                             /* HID Out Report      */
                                            /*   Bit0..7: LEDs     */


/*
 *  Get HID Input Report -> InReport
 */

void GetInReport (void) {

  if ((GPIO2 -> FIOPIN & PBINT) == 0) {             /* Check if PBINT is pressed */
    InReport = 0x01;
  } else {
    InReport = 0x00;
  }
}


/*
 *  Set HID Output Report <- OutReport
 */

void SetOutReport (void) {

  GPIO2 -> FIOCLR = LEDMSK;
  GPIO2 -> FIOSET = OutReport;	
}


/* Main Program */

int main (void) {

  SystemInit();

  GPIO2 -> FIODIR = LEDMSK;                 /* LEDs, port 2, bit 0~7 output only */

  USB_Init();                               /* USB Initialization */
  USB_Connect(TRUE);                        /* USB Connect */

  while (1);                                /* Loop forever */
}

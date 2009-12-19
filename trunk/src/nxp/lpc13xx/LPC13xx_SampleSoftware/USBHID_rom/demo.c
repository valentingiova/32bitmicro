/*----------------------------------------------------------------------------
 *      Name:    DEMO.C
 *      Purpose: USB HID Demo
 *      Version: V1.20
 *----------------------------------------------------------------------------
 *      This software is supplied "AS IS" without any warranties, express,
 *      implied or statutory, including but not limited to the implied
 *      warranties of fitness for purpose, satisfactory quality and
 *      noninfringement. Keil extends you a royalty-free right to reproduce
 *      and distribute executable files created using this software for use
 *      on NXP Semiconductors LPC microcontroller devices only. Nothing else 
 *      gives you the right to use this software.
 *
 * Copyright (c) 2009 Keil - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include "lpc13xx.h"                        /* LPC13xx definitions */
#include "type.h"

#include "usb.h"
#include "usbdesc.h"
#include "gpio.h"
#include "timer16.h"
#include "demo.h"
#include "rom_drivers.h"

extern volatile uint32_t timer16_0_counter;

uint8_t InReport;                           /* HID Input Report    */
                                            /*   Bit0   : Buttons  */
                                            /*   Bit1..7: Reserved */

uint8_t OutReport;                          /* HID Out Report      */
                                            /*   Bit0..7: LEDs     */

#define USB_VENDOR_ID 0x1FC9
#define USB_PROD_ID   0x0003
#define USB_DEVICE	  0x0100

USB_DEV_INFO DeviceInfo;
HID_DEVICE_INFO HidDevInfo;
ROM ** rom = (ROM **)0x1fff1ff8;

#define     EN_TIMER32_1    (1<<10)
#define     EN_IOCON        (1<<16)

/*
 *  Get HID Input Report -> InReport
 */

void GetInReport (uint8_t src[], uint32_t length) {
  if ( LPC_GPIO0->DATA & (1<<1) ) {		/* Check if PBINT is pressed */
    src[0] = 0x01;
  } else {
    src[0] = 0x00;
  }
  return;
}


/*
 *  Set HID Output Report <- OutReport
 */

void SetOutReport (uint8_t dst[], uint32_t length) {
  /* port2, bit 0~3 are used as LED indication from
  HID utility. */
  LPC_GPIO2->DATA &= ~(0x0F<<0);
  LPC_GPIO2->DATA |= ((dst[0])<<0);
  return; 
}

/* Main Program */
int main (void) {

  uint32_t n;

  HidDevInfo.idVendor = USB_VENDOR_ID;
  HidDevInfo.idProduct = USB_PROD_ID;
  HidDevInfo.bcdDevice = USB_DEVICE; 
  HidDevInfo.StrDescPtr = (uint32_t)&USB_StringDescriptor[0];
  HidDevInfo.InReportCount = 1;
  HidDevInfo.OutReportCount = 1;
  HidDevInfo.SampleInterval = 0x20;
  HidDevInfo.InReport = GetInReport;
  HidDevInfo.OutReport = SetOutReport;

  DeviceInfo.DevType = USB_DEVICE_CLASS_HUMAN_INTERFACE;
  DeviceInfo.DevDetailPtr = (uint32_t)&HidDevInfo;

  /* P0.1 is push-button input, P2.0~3 are LED output. */
  LPC_GPIO2->DIR |= (0x1<<0)|(0x1<<1)|(0x1<<2)|(0x1<<3);
  LPC_GPIO0->DIR &= ~(0x1<<1);

  /* 16-bit timer 0. */
  init_timer16(0, TIME_INTERVAL);
  enable_timer16(0);

  /* Set port 2_0 to output */
  GPIOSetDir( 2, 0, 1 );

  /* Enable Timer32_1 and IOCON blocks */
  LPC_SYSCON->SYSAHBCLKCTRL |= (EN_TIMER32_1 | EN_IOCON);

  (*rom)->pUSBD->init_clk_pins();   /* Use pll and pin init function in rom */

  /* insert a delay between clk init and usb init */
  for (n = 0; n < 75; n++) {}

  (*rom)->pUSBD->init(&DeviceInfo); /* USB Initialization */
  (*rom)->pUSBD->connect(TRUE);     /* USB Connect */

  while (1)                                /* Loop forever */
  {
	/* I/O configuration and LED setting pending. */
	if ( (timer16_0_counter > 0) && (timer16_0_counter <= 200) )
	{
	  GPIOSetValue( 2, 0, 0 );
	}
	if ( (timer16_0_counter > 200) && (timer16_0_counter <= 400) )
	{
	  GPIOSetValue( 2, 0, 1 );
	}
	else if ( timer16_0_counter > 400 )
	{
	  timer16_0_counter = 0;
	}
  }
}

USB_IRQHandler(void)
{
  (*rom)->pUSBD->isr();
}

/*----------------------------------------------------------------------------
 *      Name:    memory.c
 *      Purpose: USB Memory Storage Demo
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
 *      Copyright (c) 2009 Keil - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include "lpc13xx.h"
#include "usb.h"
#include "usbdesc.h"
#include "type.h"
#include "mscuser.h"
#include "memory.h"
#include "rom_drivers.h"

extern uint8_t Memory[MSC_MemorySize];         /* MSC Memory in RAM */

#define USB_VENDOR_ID 0x1FC9
#define USB_PROD_ID   0x0006
#define USB_DEVICE	  0x0100

USB_DEV_INFO DeviceInfo;
MSC_DEVICE_INFO MscDevInfo;
ROM ** rom = (ROM **)0x1fff1ff8;

#define     EN_TIMER32_1    (1<<10)
#define     EN_IOCON        (1<<16)

/* Main Program */

int main (void) {
  uint32_t n;

  for (n = 0; n < MSC_ImageSize; n++) {     /* Copy Initial Disk Image */
    Memory[n] = DiskImage[n];               /*   from Flash to RAM     */
  }

  MscDevInfo.idVendor = USB_VENDOR_ID;
  MscDevInfo.idProduct = USB_PROD_ID;
  MscDevInfo.bcdDevice = USB_DEVICE; 
  MscDevInfo.StrDescPtr = (uint32_t)&USB_StringDescriptor[0];
  MscDevInfo.MSCInquiryStr = (uint32_t)&InquiryStr[0];
  MscDevInfo.BlockSize = MSC_BlockSize;
  MscDevInfo.BlockCount = MSC_BlockCount;
  MscDevInfo.MemorySize = MSC_MemorySize;
  MscDevInfo.MSC_Read = MSC_MemoryRead;
  MscDevInfo.MSC_Write = MSC_MemoryWrite;

  DeviceInfo.DevType = USB_DEVICE_CLASS_STORAGE;
  DeviceInfo.DevDetailPtr = (uint32_t)&MscDevInfo;

  /* Enable Timer32_1 and IOCON blocks */
  LPC_SYSCON->SYSAHBCLKCTRL |= (EN_TIMER32_1 | EN_IOCON);

  (*rom)->pUSBD->init_clk_pins();   /* Use pll and pin init function in rom */

  /* insert a delay between clk init and usb init */
  for (n = 0; n < 75; n++) {
  }

  (*rom)->pUSBD->init(&DeviceInfo);  /* USB Initialization */
  init_msdstate();					 /* Initialize Storage state machine */
  (*rom)->pUSBD->connect(TRUE);      /* USB Connect */

  while (1);                                /* Loop forever */
}

USB_IRQHandler(void)
{
  (*rom)->pUSBD->isr();
}

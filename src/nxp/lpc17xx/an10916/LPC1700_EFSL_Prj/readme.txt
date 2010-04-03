
The Embedded File Systems Library (EFSL) project aims to create a library for 
file systems, to be used on various embedded systems. Currently EFSL supports 
the Microsoft FAT file system family. It is EFSL's intent to create pure ANSI 
C code that compiles on anything that bears the name 'C compiler'. 

Adding code for your specific hardware is straightforward, just add code that 
fetches or writes a 512 byte sector, and the library will do the rest. 
Existing code can of course be used, own code is only required when you have 
hardware for which no target exists. For example, it supports secure digital 
cards in SPI mode.

This project port EFSL (Rev. 0.2.8) to NXP Cortex-M3 LPC17xx MCUs.
The code is tested on MCB1768 board with 2GB MicroSD card.

Configuration:
 - Clock Settings:
   - XTAL  =  12 MHz
   - PLL0  = 288 MHz
   - CCLK  =  72 MHz
   - SSP0 PCLK = 72 MHz
 - COM settings:
 	COM1, 115200, 8-bits, no parity, 1 stop bit, XON/XOFF

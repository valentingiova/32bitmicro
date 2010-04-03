
FatFs is a generic FAT file system module for small embedded systems. 
The FatFs is written in compliance with ANSI C and completely separated from 
the disk I/O layer. Therefore it is independent of hardware architecture. 
It can be incorporated into low cost microcontrollers, such as AVR, 8051, PIC, 
ARM, Z80 and etc..., without any change. 

This project port FatFs (0.07e) to NXP Cortex-M3 LPC17xx MCUs.
The code is tested on MCB1768 board with 2GB MicroSD card.

Configuration:
 - Clock Settings:
   - XTAL  =  12 MHz
   - PLL0  = 288 MHz
   - CCLK  =  72 MHz
   - SSP0 PCLK = 72 MHz
 - COM settings:
 	COM1, 115200, 8-bits, no parity, 1 stop bit, XON/XOFF
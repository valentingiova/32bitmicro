usbmemrom
=====================
This project contains a USB Mass Storage Class example for the LPC1343
Cortex M3 microcontroller from NXP. This example uses the USB driver
in on-chip ROM, simplifying the code and saving flash space.

When downloaded to the board and executed, the PC will recognize
a USB MSC device and display a new disk drive in Windows Explorer.

0x180 bytes at the beginning of RAM have been left free for the ROM
USB driver to use.

This example can be configured by modifying the settings in config.h

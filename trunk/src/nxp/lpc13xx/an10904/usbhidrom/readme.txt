usbhidrom
=====================
This project contains a USB Human Interface Device (HID) example.
This example uses the USB driver in LPC1300 on-chip ROM, simplifying
the code and saving flash space.

When downloaded to the board and executed, the PC will recognize
a new USB HID device. Run the program "LPC1343 HID Demonstration.exe"
in the project directory to control the LEDs and buttons on the demo
board.

0x180 bytes at the beginning of RAM have been left free for the ROM
USB driver to use.

This example can be configured by modifying the settings in config.h

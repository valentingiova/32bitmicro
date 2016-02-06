# LPC1700CMSIS #

## Status ##
checked-in, integrated with 32bitmicro build environment, compiles

## Notes on using Examples ##
To reduce size of the binary elf files all of the examples in [LPC1700CMSIS/Examples](http://code.google.com/p/32bitmicro/source/browse/#svn/trunk/src/nxp/lpc17xx/LPC1700CMSIS/Examples) include individual files for the device drivers from [LPC1700CMSIS/Drivers](http://code.google.com/p/32bitmicro/source/browse/#svn/trunk/src/nxp/lpc17xx/LPC1700CMSIS/Drivers) library. These files must be compiled with settings in "lpc17xx\_libcfg.h" present in each example directory. Current makefiles do not clear object files before linking example which might cause linking errors when last configuration did not include all of the required drivers.

Currently the safest approach is to manually clear object files in [LPC1700CMSIS/Drivers/source](http://code.google.com/p/32bitmicro/source/browse/#svn/trunk/src/nxp/lpc17xx/LPC1700CMSIS/Drivers/source) before attempting to build each example.



[Release Notes](http://code.google.com/p/32bitmicro/source/browse/trunk/src/nxp/lpc17xx/LPC1700CMSIS/LPC1700CMSIS_ReleaseNotes.txt)

Original file location
[LPC17xx CMSIS-Compliant Standard Peripheral Firmware Driver Library (GNU, Keil, IAR), V1.3 (Feb 9, 2010) ](http://ics.nxp.com/support/documents/microcontrollers/zip/lpc17xx.cmsis.driver.library.zip)
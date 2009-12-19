/*****************************************************************************
 *   readme.txt:  Description of the LPC13xx Example Software Package
 *
 *   Copyright(C) 2009, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.08.31  ver 1.00    Preliminary version, first Release
 *   2009.10.21  ver 1.01    Modified system_lpc13xx.c and system_lpc13xx.h
 *                           to support Keil MDK Configuration Wizard.
 *                           SystemAHBFrequency variable has been removed from
 *                           the common directory. Added logic to distinguish 
 *                           extenal or core clock for systick timer configuration.
 *                           Added examples how to use on-chip USB HID and MSC 
 *                           drivers.
 *                           Added I2C slave example
 *                           Tested latest Keil MDK4.0, modify project to use MDK 
 *                           flash algorithm instead of in-house flash algorithm.  
 *                                                        
 *		  
 *                           
 *
******************************************************************************/

/*****************************************************************************/
Software that is described herein is for illustrative purposes only which 
provides customers with programming information regarding the products.
This software is supplied "AS IS" without any warranties. NXP Semiconductors 
assumes no responsibility or liability for the use of the software, conveys no 
license or title under any patent, copyright, or mask work right to the 
product. NXP Semiconductors reserves the right to make changes in the 
software without notification. NXP Semiconductors also make no representation 
or warranty that such application will be suitable for the specified use without 
further testing or modification.
/*****************************************************************************/


The Description of the Example software
===================

This example demonstrates the use of build-in peripherals on the NXP
LPC13xx family microcontrollers.

The Example software includes, common library, peripheral APIs, and test modules
for the APIs. The common library include startup file, standard definition and
header files, processor specific setup module, generic interrupt related APIs, 
timer routine. The peripheral directories include, ADC, GPIO, timer, SPI, I2C, 
Watchdog timer, UART, external interrupt, various USB class drivers ,etc.
  
The development environment is Keil's, an ARM company now, uVision MDK 3.85 
or later, and ULINK2 ICE. The target boards is NXP Internal Eval board with 
LPC13xx MCU on it.

Please note that, the latest Keil MDK may or may not include the startup file, 
the header files, and Cortex related API files for NVIC and Systick driver. These 
files are also included in our common library. If the users wish not to use Keil 
MDK, the compiler needs to: 
  (1) set up the include path to COMMON/INC
  (2) change #include <lpc13xx.h> to "#include "lpc13xx.h" where is located
under COMMON/INC directory. 
  (3) Add "core_cm3.c" from COMMON/SRC into your own project.

The project is created for both target option "FLASH" and "RAM". 
For "FLASH", the image code can be programmed into the flash and executed;
for "RAM", the image code can be loaded into internal SRAM(IRAM)
for easy debugging. The "RAM.ini" in each directory is a Keil uVision debugger
script file, once the debugger starts, the code will be loaded to the IRAM
first, then, "RAM.ini" will be executed and reset program counter(PC) to 
0x10000000(IRAM starting address) that code will be executed from.

Some external components, such as I2C temperature, SPI serial EEPROM, will be 
required to add on the board in order to complete the test below.

Known problem: If LPC13xx device is not listed while Cortex M3 is selected
in the device database of Keil MDK, during flash update, flash utility will 
show error message "Flash Download failure on Cortex M3" although the flash 
has been updated successfully. If LPC17xx device is selected as for LPC13xx, 
the LPC13xx flash update will succeed with no errors or warnings.


The directory tree and content of the sample software
===================

common
    -- inc
	-- lpc13xx.h		CMSIS Cortex-M3 Core Peripheral Access Layer Header 
				File for NXP LPC13xx Device Series 
	-- core_cm3.h		CMSIS Cortex-M3 Core Peripheral Access Layer Header File
	-- system_LPC13xx.h	CMSIS Cortex-M3 Device Peripheral Access Layer Header 
				File for the NXP LPC13xx Device Series
	-- type.h		Type definition Header file for NXP LPC13xx Family
	-- systick.h		Cortex M3 Systemtick header and definition 
	-- gpio.h		GPIO setting and I/O pin connfigured as external interrupt
				definition
	-- uart.h		UART setting header and definiton
	-- timer16.h		16-bit TIMER setting header and definition
	-- timer32.h		32-bit TIMER setting header and definition
	-- clkconfig.h          clock configuration header and definition  
    -- src
	-- core_cm3.c		CMSIS Cortex-M3 Core Peripheral Access Layer Source File
	-- startup_LPC13xx.s	CMSIS Cortex-M3 Core Device Startup File 
           			for the NXP LPC13xx Device Series
	-- system_LPC13xx.c	CMSIS Cortex-M3 Device Peripheral Access Layer Source
    				File for the NXP LPC13xx Device Series
	-- gpio.c		GPIO setting APIs and I/O pin connfigured as external 
				interrupt and interrupt handler
	-- uart.c		UART setting API and interrupt handler
	-- timer16.c		16-bit TIMER setting APIs and interrupt handler
	-- timer32.c		32-bit TIMER setting APIs and interrupt handler
	-- clkconfig.c		Misc. clock configuration setting and APIs in addition
				to system_lpc13xx.c  

Blinky
    -- blinky.c			General test, GPIO, Timer and NVIC test module, note: 
				API modules are in the COMMON directory and 
				shared and used by some other peripheral testing.
    -- blinky.uv2		uVision project file    

ADC
    -- adc.h			ADC header
    -- adc.c			ADC APIs
    -- adctest.c		ADC controller test module
    -- adc.uv2			uVision project file


GPIO
    -- gpiotest.c		External interrupt test module, APIs are 
				from COMMON directory
    -- gpio.uv2			uVision project file

Systick
    -- systick.c		ARM Cortext M3 Core system tick test module, APIs 
				are from COMMON directory
    -- systick.uv2		uVision project file
                
I2C
    -- i2c.h			I2C header
    -- i2c.c			I2C APIs
    -- i2ctest.c		I2C test module
    -- i2ctest.uv2		uVision project file

I2CSlave
    -- i2cslave.h		I2C slave header
    -- i2cslave.c		I2C slave APIs
    -- i2cslvtst.c		I2C slave module
    -- i2cslave.uv2		uVision project file

Timer32
    -- timer32test.c		32-bit Timer test module, note: API modules
				are in the COMMON directory and 
				shared and used by some other peripheral testing.
    -- timer32.uv2		uVision project file

UART
    -- uarttest.c		UART test module, note: UART API modules
				are in the COMMON directory, shared and used 
				by some other peripheral testing.
    -- uart.uv2			uVision project file

RS485
    -- rs485.h			RS485 header
    -- rs485.c			RS485 APIs
    -- rs485test.c		RS485 test module
    -- rs485.uv2		uVision project file

USBHID
    -- hid.h			USB HID related header
    -- hiduser.h		USB HID user specific header
    -- hiduser.c		USB HID user APIs
    -- usb.h			USB header
    -- usbcfg.h			USB configuration header
    -- usbcore.h		USB Core header
    -- usbcore.c		USB Core APIs
    -- usbdesc.h		USB descriptor header
    -- usbdesc.c		USB descriptor APIs
    -- usbhw.h			USB hardware header
    -- usbhw.c			USB hardware APIs
    -- usbreg.h			USB misc. register header
    -- usbuser.h		USB user header
    -- useuser.c		USB user APIs
    -- demo.c			USB HID test module main entry
    -- demo.h                   header file for main entry
    -- usbhid.uv2		uVision project file
	
USBMEM
    -- msc.h			USB MSC related header
    -- mscuser.h		USB MSC user specific header
    -- mscuser.c		USB MSC user APIs
    -- usb.h			USB header
    -- usbcfg.h			USB configuration header
    -- usbcore.h		USB Core header
    -- usbcore.c		USB Core APIs
    -- usbdesc.h		USB descriptor header
    -- usbdesc.c		USB descriptor APIs
    -- usbhw.h			USB hardware header
    -- usbhw.c			USB hardware APIs
    -- usbreg.h			USB misc. register header
    -- usbuser.h		USB user header
    -- useuser.c		USB user APIs
    -- diskimg.c                USB Virtual file page
    -- memory.c			USB MSC test module main entry
    -- memory.h                 header file for main entry
    -- usbmem.uv2		uVision project file

USBCDC   
    -- cdc.h			USB CDC related header
    -- cdcuser.h		USB CDC Device Class user specific header
    -- cdcuser.c		USB CDC Device Class user APIs
    -- usb.h			USB header
    -- usbcfg.h			USB configuration header
    -- usbcore.h		USB Core header
    -- usbcore.c		USB Core APIs
    -- usbdesc.h		USB descriptor header
    -- usbdesc.c		USB descriptor APIs
    -- usbhw.h			USB hardware header
    -- usbhw.c			USB hardware APIs
    -- usbreg.h			USB misc. register header
    -- usbuser.h		USB user header
    -- usbuser.c		USB user APIs
    -- vcomdemo.h		header for VCOM demo
    -- vcomdemo.c		USB CDC(Virtual COM) test module, main entry
    -- virtualCom.uv2		uVision project file
    -- serial.h			Header for UART port
    -- serial.c			UART module APIs
    -- mcb1700-vcom.inf		The host side driver installation file
	
WDT
    -- wdt.h			Watchdog timer header
    -- wdt.c			Watchdog timer APIs
    -- wdttest.c		Watchdog timer test module
    -- wdt.uv2			uVision project file


USBHID_rom(Using on-chip USB HID driver example)
    -- usb.h			USB header
    -- rom_drivers.h            On-chip USB driver header
    -- usbdesc.h		USB descriptor header
    -- usbdesc.c		USB descriptor APIs
    -- demo.c			USB HID test module main entry
    -- demo.h                   header file for main entry
    -- usbhid.uv2		uVision project file
    -- flash.ini                Keil MDK Debugger config and initialization file.
	
USBMEM_rom(Using on-chip USB MSC driver example)
    -- mscuser.h		USB MSC user specific header
    -- mscuser.c		USB MSC user APIs
    -- usb.h			USB header
    -- rom_drivers.h            On-chip USB driver header
    -- usbdesc.h		USB descriptor header
    -- usbdesc.c		USB descriptor APIs
    -- diskimg.c                USB Virtual file page
    -- memory.c			USB MSC test module main entry
    -- memory.h                 header file for main entry
    -- usbmem.uv2		uVision project file
    -- flash.ini                Keil MDK Debugger config and initialization file.

========================================================================
    MAKEFILE PROJECT : LPC13xx_SampleSoftware.101 Project Overview
========================================================================

AppWizard has created this LPC13xx_SampleSoftware.101 project for you.  

This file contains a summary of what you will find in each of the files that
make up your LPC13xx_SampleSoftware.101 project.


LPC13xx_SampleSoftware.101.vcproj
    This is the main project file for VC++ projects generated using an Application Wizard. 
    It contains information about the version of Visual C++ that generated the file, and 
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

This project allows you to build/clean/rebuild from within Visual Studio by calling the commands you have input 
in the wizard. The build command can be nmake or any other tool you use.

This project  does not contain any files, so there are none displayed in Solution Explorer.

/////////////////////////////////////////////////////////////////////////////

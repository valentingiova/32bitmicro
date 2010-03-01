#
# * 32bitmicro NXP lpc17xx LPC1700CMSIS Examples Makefile
# * $URL$
# * $ID$
#
#Copyright (c) 2010, 32bitmicro
#All rights reserved.
#
#Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
#Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
#Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation 
#and/or other materials provided with the distribution.
#Neither the name of the 32bitmicro nor the names of its contributors may be used to endorse or promote products derived from this software without 
#specific prior written permission.
#
#THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
#BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
#SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
#DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
#OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
#NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

# sub-projects

SUBDIRS = \
ADC/Polling \
CAN/CAN_AFLUT_dynamic \
CAN/CAN_test_AFLUT \
CAN/CAN_test_bypass_mode \
CAN/CAN_test_two_kit \
DAC/DAC \
DAC/DMA \
EMAC/Easy_Web \
EMAC/EmacRaw \
EMAC/uIP \
GPDMA/Mem_2_Mem_Test \
GPIO/EINT_PowerDown \
GPIO/GPIO_Interrupt \
GPIO/LedBlinky \
GPIO/Port_LCD \
I2C/Master_Slave_Interrupt \
I2C/master \
I2C/pca8581_polling \
I2C/sc16is750_int \
I2C/sc16is750_polling \
I2C/slave \
I2S/I2S_DMA \
I2S/I2S_IRQ \
I2S/I2S_test_4_wire \
I2S/I2S_two_kit \
I2S/Polling \
MCPWM/MCPWMSimple \
PWM/Dual_Edge \
PWM/Match_Interrupt \
PWM/Single_Edge \
QEI/QEI_Velo \
RIT/Interrupt \
RIT/Polling \
RIT/Simple \
RTC/AlarmCntIncrInterrupt \
SPI/LoopBack \
SPI/Master \
SPI/Slave \
SPI/sc16is750_int \
SPI/sc16is750_polling \
SSP/Master \
SSP/MicroWire \
SSP/Slave \
SSP/TI \
SSP/dma \
SSP/sc16is750_int \
SSP/sc16is750_polling \
TIMER/Capture \
TIMER/Delay \
TIMER/Interrupt_Match \
UART/AutoBaud \
UART/DMA \
UART/Interrupt \
UART/Polling \
UART/RS485_Master \
UART/RS485_Slave \
UART/UART1_FullModem \
USBDEV/USBHID \
USBDEV/USBMem \
WDT/INTERRUPT \
WDT/RESET



all:
	@for dir in $(SUBDIRS); do \
		echo "Building " $$dir;\
		$(MAKE) -f Makefile -C $$dir;\
	done
	
clean:
	@for dir in $(SUBDIRS); do \
		echo "Cleaning " $$dir;\
		$(MAKE) -f Makefile -C $$dir clean;\
	done

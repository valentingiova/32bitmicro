/*
 * 32bitmicro startup_LPC13xx.S  Startup File for the NXP LPC13xx Device Series 

 * $URL$
 * $ID$

Copyright (c) 2009, 32bitmicro
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation 
and/or other materials provided with the distribution.
Neither the name of the 32bitmicro nor the names of its contributors may be used to endorse or promote products derived from this software without 
specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

	.syntax unified
	.cpu cortex-m3
	.fpu softvfp
	.thumb

/* interrupt vectors table */

	.global	__isr_vectors
	.weak	__isr_vectors

 	.section ".isr_vector","a",%progbits
	.type	__isr_vectors, %object
	.size	__isr_vectors, .-__isr_vectors


__isr_vectors:
	.word	_estack                   /*  0 Top of Stack                 */
/* CM3 system interrupts */
	.word	Reset_Handler             /*  1 Reset Handler                */
	.word	NMI_Handler               /*  2 NMI Handler                  */
	.word	HardFault_Handler         /*  3 Hard Fault Handler           */
	.word	MemManage_Handler         /*  4 MPU Fault Handler            */
	.word	BusFault_Handler          /*  5 Bus Fault Handler            */
	.word	UsageFault_Handler        /*  6 Usage Fault Handler          */
	.word	0                         /*  7 Reserved                     */
	.word	0                         /*  8 Reserved                     */
	.word	0                         /*  9 Reserved                     */
	.word	0                         /* 10 Reserved                     */
	.word	SVC_Handler               /* 11 SVCall Handler               */
	.word	DebugMon_Handler          /* 12 Debug Monitor Handler        */
	.word	0                         /* 13 Reserved                     */
	.word	PendSV_Handler            /* 14 PendSV Handler               */
	.word	SysTick_Handler           /* 15 SysTick Handler              */

/* LPC13xx interrupts */
	.word   WAKEUP_IRQHandler         /* 16  0 Wake-up on  pin  PIO0_0             */
	.word   WAKEUP_IRQHandler         /* 17  1 Wake-up on  pin  PIO0_1             */
	.word   WAKEUP_IRQHandler         /* 18  2 Wake-up on  pin  PIO0_2             */
	.word   WAKEUP_IRQHandler         /* 19  3 Wake-up on  pin  PIO0_3             */
	.word   WAKEUP_IRQHandler         /* 20  4 Wake-up on  pin  PIO0_4             */
 	.word   WAKEUP_IRQHandler         /* 21  5 Wake-up on  pin  PIO0_5             */
	.word   WAKEUP_IRQHandler         /* 22  6 Wake-up on  pin  PIO0_6             */
	.word   WAKEUP_IRQHandler         /* 23  7 Wake-up on  pin  PIO0_7             */	
	.word   WAKEUP_IRQHandler         /* 24  8 Wake-up on  pin  PIO0_8             */
	.word   WAKEUP_IRQHandler         /* 25  9 Wake-up on  pin  PIO0_9             */
	.word   WAKEUP_IRQHandler         /* 26 10 Wake-up on  pin  PIO0_10            */
	.word   WAKEUP_IRQHandler         /* 27 11 Wake-up on  pin  PIO0_11            */
	.word   WAKEUP_IRQHandler         /* 28 12 Wake-up on  pin  PIO1_0             */
	.word   WAKEUP_IRQHandler         /* 29 13 Wake-up on  pin  PIO1_1             */
	.word   WAKEUP_IRQHandler         /* 30 14 Wake-up on  pin  PIO1_2             */
	.word   WAKEUP_IRQHandler         /* 31 15 Wake-up on  pin  PIO1_3             */
	.word   WAKEUP_IRQHandler         /* 32 16 Wake-up on  pin  PIO1_4             */
	.word   WAKEUP_IRQHandler         /* 33 17 Wake-up on  pin  PIO1_5             */
	.word   WAKEUP_IRQHandler         /* 34 18 Wake-up on  pin  PIO1_6             */
	.word   WAKEUP_IRQHandler         /* 35 19 Wake-up on  pin  PIO1_7             */
	.word   WAKEUP_IRQHandler         /* 36 20 Wake-up on  pin  PIO1_8             */
	.word   WAKEUP_IRQHandler         /* 37 21 Wake-up on  pin  PIO1_9             */
	.word   WAKEUP_IRQHandler         /* 38 22 Wake-up on  pin  PIO1_10            */
	.word   WAKEUP_IRQHandler         /* 39 23 Wake-up on  pin  PIO1_11            */
	.word   WAKEUP_IRQHandler         /* 40 24 Wake-up on  pin  PIO2_0             */
	.word   WAKEUP_IRQHandler         /* 41 25 Wake-up on  pin  PIO2_1             */
	.word   WAKEUP_IRQHandler         /* 42 26 Wake-up on  pin  PIO2_2             */
	.word   WAKEUP_IRQHandler         /* 43 27 Wake-up on  pin  PIO2_3             */
	.word   WAKEUP_IRQHandler         /* 44 28 Wake-up on  pin  PIO2_4             */
	.word   WAKEUP_IRQHandler         /* 45 29 Wake-up on  pin  PIO2_5             */
	.word   WAKEUP_IRQHandler         /* 46 30 Wake-up on  pin  PIO2_6             */
	.word   WAKEUP_IRQHandler         /* 47 31 Wake-up on  pin  PIO2_7             */
	.word   WAKEUP_IRQHandler         /* 48 32 Wake-up on  pin  PIO2_8             */
	.word   WAKEUP_IRQHandler         /* 49 33 Wake-up on  pin  PIO2_9             */
	.word   WAKEUP_IRQHandler         /* 50 34 Wake-up on  pin  PIO2_10            */
	.word   WAKEUP_IRQHandler         /* 51 35 Wake-up on  pin  PIO2_11            */
	.word   WAKEUP_IRQHandler         /* 52 36 Wake-up on  pin  PIO3_0             */
	.word   WAKEUP_IRQHandler         /* 53 37 Wake-up on  pin  PIO3_1             */	
	.word   WAKEUP_IRQHandler         /* 54 38 Wake-up on  pin  PIO3_2             */
	.word   WAKEUP_IRQHandler         /* 55 39 Wake-up on  pin  PIO3_3             */
	.word   I2C_IRQHandler            /* 56 40 I2C0 SI (state change)    */
	.word   TIMER16_0_IRQHandler      /* 57 41 CT16B0 16 bit timer 0     */
	.word   TIMER16_1_IRQHandler      /* 58 42 CT16B1 16 bit timer 1     */
	.word   TIMER32_0_IRQHandler      /* 59 43 CT32B0 32 bit timer 0     */
	.word   TIMER32_1_IRQHandler      /* 60 44 CT32B1 32 bit timer 1     */
	.word   SSP_IRQHandler            /* 61 45 SSP                       */
	.word   UART_IRQHandler           /* 62 46 UART                      */
	.word   USB_IRQHandler            /* 63 47 USB IRQ low priority      */
	.word   USB_FIQHandler            /* 64 48 USB FIQ high priority     */
	.word   ADC_IRQHandler            /* 65 49 ADC end of conversion     */
	.word   WDT_IRQHandler            /* 66 50 Watchdog interrupt (WDINT)                  */
	.word   BOD_IRQHandler            /* 67 51 BOD Brown-out detect                        */
	.word   FMC_IRQHandler            /* 68 52 Reserved also marked as IP2111 Flash Memory */
	.word   PIOINT3_IRQHandler        /* 69 53 PIO_3  GPIO interrupt status of port 3      */
	.word   PIOINT2_IRQHandler        /* 70 54 PIO_2  GPIO interrupt status of port 2      */
	.word   PIOINT1_IRQHandler        /* 71 55 PIO_1  GPIO interrupt status of port 1      */
	.word   PIOINT0_IRQHandler        /* 72 56 PIO_0  GPIO interrupt status of port 0      */


/* Reset handler */
	.section ".text.handler.reset","x",%progbits

Reset_Handler:
	.thumb_func
	.globl  Reset_Handler
	.type   Reset_Handler, %function
	ldr     r0, =SystemInit
	blx     r0
	/* branch to entry point */
	ldr     r0, =_start+1
	bx      r0
	.size	Reset_Handler, .-Reset_Handler


/* Dummy handlers */
	.section ".text.handler.dummy","x",%progbits

NMI_Handler:
	.globl  NMI_Handler
	.weak   NMI_Handler
	.type   NMI_Handler, %function
	b .

HardFault_Handler:
	.globl  HardFault_Handler         
	.weak   HardFault_Handler
	.type   HardFault_Handler, %function
	b .

MemManage_Handler:
	.globl  MemManage_Handler
	.weak   MemManage_Handler
	.type   MemManage_Handler, %function
	b .

BusFault_Handler:
	.globl  BusFault_Handler
	.weak   BusFault_Handler
	.type   BusFault_Handler, %function
	b .

UsageFault_Handler:
	.globl  UsageFault_Handler
	.weak   UsageFault_Handler
	.type   UsageFault_Handler, %function    
	b .

SVC_Handler:
	.globl  SVC_Handler
	.weak   SVC_Handler
	.type   SVC_Handler, %function    
	b .

DebugMon_Handler:
	.globl  DebugMon_Handler
	.weak   DebugMon_Handler
	.type   DebugMon_Handler, %function    
	b .

PendSV_Handler:
	.globl  PendSV_Handler
	.weak   PendSV_Handler
	.type   PendSV_Handler, %function    
	b .

SysTick_Handler:
	.globl  SysTick_Handler
	.weak   SysTick_Handler
	.type   SysTick_Handler, %function    
	b .

/* Default handler */
	.section ".text.handler.default","x",%progbits

	.global	Default_Handler
	.weak	Default_Handler

Default_Handler:
	.globl    WAKEUP_IRQHandler
	.weak     WAKEUP_IRQHandler
	.globl    I2C_IRQHandler
	.weak     I2C_IRQHandler
	.globl    TIMER16_0_IRQHandler
	.weak     TIMER16_0_IRQHandler
	.globl    TIMER16_1_IRQHandler
	.weak     TIMER16_1_IRQHandler
	.globl    TIMER32_0_IRQHandler
	.weak     TIMER32_0_IRQHandler
	.globl    TIMER32_1_IRQHandler
	.weak     TIMER32_1_IRQHandler
	.globl    SSP_IRQHandler
	.weak     SSP_IRQHandler
	.globl    UART_IRQHandler
	.weak     UART_IRQHandler
	.globl    USB_IRQHandler
	.weak     USB_IRQHandler
	.globl    USB_FIQHandler
	.weak     USB_FIQHandler
	.globl    ADC_IRQHandler
	.weak     ADC_IRQHandler
	.globl    WDT_IRQHandler
	.weak     WDT_IRQHandler
	.globl    BOD_IRQHandler
	.weak     BOD_IRQHandler
	.globl    FMC_IRQHandler
	.weak     FMC_IRQHandler
	.globl    PIOINT3_IRQHandler
	.weak     PIOINT3_IRQHandler
	.globl    PIOINT2_IRQHandler
	.weak     PIOINT2_IRQHandler
	.globl    PIOINT1_IRQHandler
	.weak     PIOINT1_IRQHandler
	.globl    PIOINT0_IRQHandler
	.weak     PIOINT0_IRQHandler

WAKEUP_IRQHandler:
I2C_IRQHandler:
TIMER16_0_IRQHandler:
TIMER16_1_IRQHandler:
TIMER32_0_IRQHandler:
TIMER32_1_IRQHandler:
SSP_IRQHandler:
UART_IRQHandler:
USB_IRQHandler:
USB_FIQHandler:
ADC_IRQHandler:
WDT_IRQHandler:
BOD_IRQHandler:
FMC_IRQHandler:
PIOINT3_IRQHandler:
PIOINT2_IRQHandler:
PIOINT1_IRQHandler:
PIOINT0_IRQHandler:

/* catch it here */
	b .
	.size	Default_Handler, .-Default_Handler

/* Default _start */

	.section ".text"
	.thumb
	.global	_start
	.weak	_start
	.type   _start, %function    
_start:

/* fill .bss with 0 using byte stores */
	ldr     r0, =_bss
	ldr     r1, =_ebss
        mov     r2, #0
.L0:
	strb	r2, [r0], #1
	cmp     r0, r1
  	bcc.n   .L0

/* copy initialized .data from rom to ram */
	ldr     r0, =_data
	ldr     r1, =_edata
	ldr     r2, =_ldata
.L1:
	ldrb	r3, [r2], #1
	strb	r3, [r0], #1
	cmp     r0, r1
	bcc.n   .L1

/* branch to main */
	ldr     r0, =main+1
	bx      r0 
	.size	_start, .-_start


	.section ".CRP._0x02FC","a",%progbits
CRP_Key:
	.word     0xFFFFFFFF
	
	.end

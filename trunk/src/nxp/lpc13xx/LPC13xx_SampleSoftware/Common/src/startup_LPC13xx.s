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


/* Linker symbols */
/* .text section */
	.word	_text
	.word	_etext

/* .isr_vector section */
	.word	_vector
	.word	_evector

/* .data section */
	.word	_data
	.word	_edata

/* .bss section */
	.word	_bss
	.word	_ebss

/* .heap section at the end of bss */
	.word	_heap
	.word	_eheap

/* .stack section stack top at the end of ram set by linker */
	.word	_stack
	.word	_estack

/* System Stack */
	.globl  __stack
	.globl  __stack_size

	.equ    Stack_Size, 0x0000040
	.section	".stack", "w"

__stack:
	.if     Stack_Size
	.space  Stack_Size
	.endif
	.set    __stack_size, .-__stack

/* System Heap */
	.globl  __heap
	.globl  __heap_size

	.equ    Heap_Size, 0x00000100
	.section	".heap", "w"

__heap:
	.if     Heap_Size
	.space  Heap_Size
	.endif
	.set    __heap_size, .-__heap

/* interrupt vectors table */

	.global	__isr_vectors
	.weak	__isr_vectors

 	.section ".isr_vector","a",%progbits
	.type	__isr_vectors, %object
	.size	__isr_vectors, .-__isr_vectors


__isr_vectors:
	.long	_estack                   /*  0: Top of Stack                 */
/* CM3 system interrupts */
	.long	Reset_Handler             /*  1: Reset Handler                */
	.long	NMI_Handler               /*  2: NMI Handler                  */
	.long	HardFault_Handler         /*  3: Hard Fault Handler           */
	.long	MemManage_Handler         /*  4: MPU Fault Handler            */
	.long	BusFault_Handler          /*  5: Bus Fault Handler            */
	.long	UsageFault_Handler        /*  6: Usage Fault Handler          */
	.long	0                         /*  7: Reserved                     */
	.long	0                         /*  8: Reserved                     */
	.long	0                         /*  9: Reserved                     */
	.long	0                         /* 10: Reserved                     */
	.long	SVC_Handler               /* 11: SVCall Handler               */
	.long	DebugMon_Handler          /* 12: Debug Monitor Handler        */
	.long	0                         /* 13: Reserved                     */
	.long	PendSV_Handler            /* 14: PendSV Handler               */
	.long	SysTick_Handler           /* 15: SysTick Handler              */

/* LPC13xx interrupts */
    .long   WAKEUP_IRQHandler           /* 16+ 0: Wakeup PIO0.0          */
    .long   WAKEUP_IRQHandler           /* 16+ 1: Wakeup PIO0.1          */
    .long   WAKEUP_IRQHandler           /* 16+ 2: Wakeup PIO0.2          */
    .long   WAKEUP_IRQHandler           /* 16+ 3: Wakeup PIO0.3          */
    .long   WAKEUP_IRQHandler           /* 16+ 4: Wakeup PIO0.4          */
    .long   WAKEUP_IRQHandler           /* 16+ 5: Wakeup PIO0.5          */
    .long   WAKEUP_IRQHandler           /* 16+ 6: Wakeup PIO0.6          */
    .long   WAKEUP_IRQHandler           /* 16+ 7: Wakeup PIO0.7          */
    .long   WAKEUP_IRQHandler           /* 16+ 8: Wakeup PIO0.8          */
    .long   WAKEUP_IRQHandler           /* 16+ 9: Wakeup PIO0.9          */
    .long   WAKEUP_IRQHandler           /* 16+10: Wakeup PIO0.10         */
    .long   WAKEUP_IRQHandler           /* 16+11: Wakeup PIO0.11         */
    .long   WAKEUP_IRQHandler           /* 16+12: Wakeup PIO1.0          */
    .long   WAKEUP_IRQHandler           /* 16+13: Wakeup PIO1.1          */
    .long   WAKEUP_IRQHandler           /* 16+14: Wakeup PIO1.2          */
    .long   WAKEUP_IRQHandler           /* 16+15: Wakeup PIO1.3          */
    .long   WAKEUP_IRQHandler           /* 16+16: Wakeup PIO1.4          */
    .long   WAKEUP_IRQHandler           /* 16+17: Wakeup PIO1.5          */
    .long   WAKEUP_IRQHandler           /* 16+18: Wakeup PIO1.6          */
    .long   WAKEUP_IRQHandler           /* 16+19: Wakeup PIO1.7          */
    .long   WAKEUP_IRQHandler           /* 16+20: Wakeup PIO1.8          */
    .long   WAKEUP_IRQHandler           /* 16+21: Wakeup PIO1.9          */
    .long   WAKEUP_IRQHandler           /* 16+22: Wakeup PIO1.10         */
    .long   WAKEUP_IRQHandler           /* 16+23: Wakeup PIO1.11         */
    .long   WAKEUP_IRQHandler           /* 16+24: Wakeup PIO2.0          */
    .long   WAKEUP_IRQHandler           /* 16+25: Wakeup PIO2.1          */
    .long   WAKEUP_IRQHandler           /* 16+26: Wakeup PIO2.2          */
    .long   WAKEUP_IRQHandler           /* 16+27: Wakeup PIO2.3          */
    .long   WAKEUP_IRQHandler           /* 16+28: Wakeup PIO2.4          */
    .long   WAKEUP_IRQHandler           /* 16+29: Wakeup PIO2.5          */
    .long   WAKEUP_IRQHandler           /* 16+30: Wakeup PIO2.6          */
    .long   WAKEUP_IRQHandler           /* 16+31: Wakeup PIO2.7          */
    .long   WAKEUP_IRQHandler           /* 16+32: Wakeup PIO2.8          */
    .long   WAKEUP_IRQHandler           /* 16+33: Wakeup PIO2.9          */
    .long   WAKEUP_IRQHandler           /* 16+34: Wakeup PIO2.10         */
    .long   WAKEUP_IRQHandler           /* 16+35: Wakeup PIO2.11         */
    .long   WAKEUP_IRQHandler           /* 16+36: Wakeup PIO3.0          */
    .long   WAKEUP_IRQHandler           /* 16+37: Wakeup PIO3.1          */
    .long   WAKEUP_IRQHandler           /* 16+38: Wakeup PIO3.2          */
    .long   WAKEUP_IRQHandler           /* 16+39: Wakeup PIO3.3          */
    .long   I2C_IRQHandler              /* 16+40: I2C                    */
    .long   TIMER16_0_IRQHandler        /* 16+41: 16-bit Counter-Timer 0 */
    .long   TIMER16_1_IRQHandler        /* 16+42: 16-bit Counter-Timer 1 */
    .long   TIMER32_0_IRQHandler        /* 16+43: 32-bit Counter-Timer 0 */
    .long   TIMER32_1_IRQHandler        /* 16+44: 32-bit Counter-Timer 1 */
    .long   SSP_IRQHandler              /* 16+45: SSP                    */
    .long   UART_IRQHandler             /* 16+46: UART                   */
    .long   USB_IRQHandler              /* 16+47: USB IRQ                */
    .long   USB_FIQHandler              /* 16+48: USB FIQ                */
    .long   ADC_IRQHandler              /* 16+49: A/D Converter          */
    .long   WDT_IRQHandler              /* 16+50: Watchdog Timer         */
    .long   BOD_IRQHandler              /* 16+51: Brown Out Detect       */
    .long   FMC_IRQHandler              /* 16+52: IP2111 Flash Memory    */
    .long   PIOINT3_IRQHandler          /* 16+53: PIO INT3               */
    .long   PIOINT2_IRQHandler          /* 16+54: PIO INT2               */
    .long   PIOINT1_IRQHandler          /* 16+55: PIO INT1               */
    .long   PIOINT0_IRQHandler          /* 16+56: PIO INT0               */
/*
		.section ".CRP._0x02FC","a",%progbits
CRP_Key         .long     0xFFFFFFFF
                .endif
*/
    .thumb


Reset_Handler:
	.fnstart
/* fill .bss with 0 using byte stores */
	ldr     r0, =_bss
	ldr     r1, =_ebss
        mov     r2, #0
.L0:
	strb	r2, [r0], #1			/* post index */
	cmp     r0, r1
	blt     .L0

/* copy initialized .data from rom to ram */
	ldr     r0, =_data
	ldr     r1, =_edata
        mov     r2, #0
.L1:
	ldrb	r3, [r0], #1			/* post index */
	strb	r3, [r2], #1			/* post index */
	cmp     r0, r1
	blt     .L1

/* branch to entry point */
	ldr     r0, =_start
        bx      r0
	.cantunwind
        .fnend   
	.size	Reset_Handler, .-Reset_Handler



/* default handlers */
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

	.global	Default_Handler
	.weak	Default_Handler

	.section	.text.Default_Handler,"ax",%progbits
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
        b       .
        .size	Default_Handler, .-Default_Handler
    .end

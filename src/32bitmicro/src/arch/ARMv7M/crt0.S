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
	/* .cpu cortex-m3 */
	/* .fpu softvfp   */
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
   	

	.thumb
/* Startup code */
	.text
   	.thumb_func
	.align 	0
	.global	_mainCRTStartup
	.global	_start
	.global	start
	.type   _start, %function
_start:
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

/* branch to main entry point */
	ldr     r0, =main
        bx      r0
	.cantunwind
        .fnend   
	.size	start, .-start


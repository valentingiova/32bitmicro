# -----------------------------------------------------------------------
#
#   Copyright 2003-2008 H. Peter Anvin - All Rights Reserved
#
#   Permission is hereby granted, free of charge, to any person
#   obtaining a copy of this software and associated documentation
#   files (the "Software"), to deal in the Software without
#   restriction, including without limitation the rights to use,
#   copy, modify, merge, publish, distribute, sublicense, and/or
#   sell copies of the Software, and to permit persons to whom
#   the Software is furnished to do so, subject to the following
#   conditions:
#
#   The above copyright notice and this permission notice shall
#   be included in all copies or substantial portions of the Software.
#
#   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
#   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
#   OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
#   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
#   HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
#   WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
#   OTHER DEALINGS IN THE SOFTWARE.
#
# -----------------------------------------------------------------------

# COM32 start up code - must be linked first in the binary

        .data
        .globl  gdt
        .globl  gdtr
        .globl  idt
        .globl  idtr
gdt:    .space  64      # must equal NGD*8 (64 = 8 segments)
gdtr:   .word   63      # sizeof _gdt -1 (in bytes)
        .long   gdt
idt:    .space  384     # must equal NID*8 (384 == 48 vectors)
idtr:   .word   383     # size of _idt -1 (in bytes)
        .long   idt

        .globl cpudelay

cpudelay:       .long   1
        .text
        .align 2
        .globl  _end
        .globl  _edata
        .globl  nulluser
        .globl  _bootdev
        .globl  _cyloffset
        .globl  lidt

        .globl  __zero                  # artificial value for entry point
        .set    __zero,0

	.globl com32topmem		# com32 top memory
com32topmem:	.long 0


		.section ".text","ax"
		.globl start
		.globl _start
start:
_start:
		# This first instruction acts as COM32 magic number
		movl $0x21cd4cff,%eax

# com32 X
#		movl	$0x0200,%eax
#		movl	$'X',   %edx
#		int	$0x21
		.globl  putchar_com32
		movl	$'X',   %eax
#		push	%eax
#		call	putchar_com32

# store top of the memory
		movl $com32topmem,%eax
		movl %esp,(%eax)

	
		# Upwards string operations
		cld

		# Zero the .bss segment
		xorl %eax,%eax
		movl $__bss_start,%edi		# Symbol provided by linker
		movl $_end+3,%ecx		# Symbol provided by linker
		subl %edi,%ecx
		shrl $2,%ecx
		rep ; stosl

		# Copy COM32 invocation parameters
		leal 4(%esp),%esi		# Argument list
		movl $__com32,%edi
		movl $6,%ecx
		movl %esp,-4(%edi)		# Save the initial stack ptr
		cmpl (%esi),%ecx
		jbe 1f
		movl (%esi),%ecx
1:		rep ; movsl


		# XINU

# com32 X
#		movl	$0x0200,%eax
#		movl	$'X',   %edx
#		int	$0x21

#if 0
	/* this part does not work under com32 */

		call    setsegs
		lgdt    gdtr
        /*
         * reload segment registers; we do code segment by a far
         * jump
         */
		ljmp    $0x8,$gdt1      /* CS descriptor 1 */
gdt1:
		movl    $0x10,%eax      /* DS descriptor 2 */
		movw    %ax,%ds
		movw    %ax,%es
		movl    $0x18,%eax      /* SS descriptor 3 */
		movw    %ax,%ss
		movl    initsp,%esp     /* set new stack pointer base */
		movl    %esp,%ebp
#endif
	
		call	nulluser
		call	halt
		jmp	_start

		# Run program; we call this __start rather than main since we
		# did not parse the command line or anything like that.
#		jmp __start


/*
 * delay - spin-loop delay in units of 10 microseconds
 */
	.text
	.globl delay
delay:
	pushl	%ebp
	movl	%esp,%ebp
	movl	8(%ebp),%eax
L4:
	decl	%eax
	jle	L3
	movl	cpudelay,%edx
L2:
	decl	%edx
	jge	L2
	jmp	L4
L3:
	leave
	ret

	.globl	inb
inb:	movl	4(%esp),%edx
	xorl	%eax,%eax	# clr eax
	inb	%dx,%al
	ret

	.globl	inw
inw:	movl	4(%esp),%edx
	xorl	%eax,%eax	# clr eax
	inw	%dx,%ax
	ret

	.globl	outb
outb:	movl	4(%esp),%edx
	movl	8(%esp),%eax
	outb	%al,%dx
	ret

	.globl	outw
outw:	movl	4(%esp),%edx
	movl	8(%esp),%eax
	outw	%ax,%dx
	ret

        #
        # lidt() - load interrupt descriptor table from _idtr
        #
lidt:
###        lidt    idtr
        ret

		.section ".bss","aw"
		.globl __entry_esp
__entry_esp:	.space 4
		.globl __com32
__com32:	.space 4*6

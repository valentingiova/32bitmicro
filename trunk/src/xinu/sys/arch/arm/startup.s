/*
 * Startup code for standalone system
 */

	.data
	
	.globl _cpudelay
	.globl cpudelay

_cpudelay:
cpudelay:	.long	1
	.text
	.align 2
	.globl	_end
	.globl	_edata
	.globl	_nulluser
	.globl	_bootdev
	.globl	_cyloffset
	.globl	_lidt

	.globl	__zero			@ artificial value for entry point
	.set	__zero,0



entry:	.globl	entry
	.globl	_start
	.globl	start

	/* relocate program and enter at symbol "_start" */

@	pushl	$_start
@	ret

_start:
start:

	/* setup stack pointer */


	/*
	 * Clear Bss and up to 64K heap
	 */

@	movl	$64*1024,%ebx
@	movl	$_end,%eax	# should be movl $_end-_edata but ...
@	subl	$_edata,%eax
@	addl	%ebx,%eax
@	pushl	%eax
@	pushl	$_edata
@	call	_bzero


	/*
	 * Clear 64K of stack
	 */
@	movl	%esi,%eax
@	subl	%ebx,%eax
@	subl	$5*4,%ebx
@	pushl	%ebx
@	pushl	%eax
@	call	_bzero
@	movl	%esi,%esp

@	movl	_initsp,%esp	/* set new stack pointer base */
@	movl	%esp,%ebp

@	call	_nulluser
@	call	_halt
@	jmp	_start
	bx lr

	.data
_bootdev:	.long	0
_cyloffset:	.long	0
savearea:	.long	0,0	@ sp & bp to return to
/*
 * _delay - spin-loop delay in units of 10 microseconds
 */
	.text
	.globl _delay
	.globl delay
_delay:
delay:
	bx lr

	.globl	_rtcin
_rtcin:
	bx lr

	.globl ___udivsi3
___udivsi3:
	bx lr

	.globl ___divsi3
___divsi3:
	bx lr

	@
	@ bzero (base,cnt)
	@

	.globl _bzero
_bzero:
	bx lr

	@
	@ bcopy(src, dst, count)
	@

	.globl	_bcopy
_bcopy:
	bx lr


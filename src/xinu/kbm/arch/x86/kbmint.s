/* kbmint.s - kbmint */

#include <icu.s>

/*------------------------------------------------------------------------
 * kbmint  --  interrupt handler for keyboard input
 *------------------------------------------------------------------------
 */
	.text
	.globl	kbmint
	.globl	_kbmint

kbmint:
_kbmint:
	cli
	pushal
	movb	$EOI,%al
	outb	%al,$OCW1_2
	call	kbmiin
	popal
	sti
	iret

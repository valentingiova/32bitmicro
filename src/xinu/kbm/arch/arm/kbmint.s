/* kbmint.s - kbmint */

#include <icu.s>

/*------------------------------------------------------------------------
 * kbmint  --  interrupt handler for keyboard input
 *------------------------------------------------------------------------
 */
	.text
	.globl	_kbmint
	.globl	kbmint

_kbmint:
kbmint:
	bx lr

/* comint.s - comint */

#include <icu.s>

/*------------------------------------------------------------------------
 * comint  --  interrupt handler for SLU input
 *------------------------------------------------------------------------
 */
	.text
	.globl	_comint
	.globl	comint

_comint:
comint:

	bx lr

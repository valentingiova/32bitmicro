/* clkint.s - _clkint */

#include <icu.s>

		.data
count100:	.long	100
		.text
		.globl	_clkint
		.globl	clkint
_clkint:
clkint:
/*		call	_wakeup */
clpreem:	#decl	_preempt
#		ja	clret
/*		call	_resched */
clret:
		bx lr

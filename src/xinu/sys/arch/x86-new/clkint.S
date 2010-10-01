/* clkint.s - _clkint */

#include <icu.s>
		.text
count100:	.word	100
		.globl	_clkint
		.globl	clkint
_clkint:
clkint:
		cli
		pushal
		movb	$EOI,%al
		outb	%al,$OCW1_2

		incl	_ctr100
		subw	$1,count100
		ja	cl1
		incl	_clktime
		movw	$100,count100
cl1:
		cmpl	$0,_slnempty
		je	clpreem
		movl	_sltop,%eax
		decl	(%eax)
		ja	clpreem
		call	_wakeup
clpreem:	decl	_preempt
		ja	clret
		call	_resched
clret:
		popal
		sti
		iret

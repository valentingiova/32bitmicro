/* clkint.s - _clkint */

#include <icu.s>

		.data
count100:	.long	100
		.text
		.globl	clkint
clkint:
		cli
		pushal
		movb	$EOI,%al
		outb	%al,$OCW1_2

		incl	ctr100
		subl	$1,count100
		ja	cl1
		incl	clktime
		movl	$100,count100
cl1:
		cmpl	$0,slnempty
		je	clpreem
		movl	sltop,%eax
		decl	(%eax)
		ja	clpreem
		call	wakeup
clpreem:	decl	preempt
		ja	clret
		call	resched
clret:
		popal
		sti
		iret

/* ue_int.s - _ue_int */

#include <icu.s>

		.text
		.globl	ue_int
		.globl	_ue_int
ue_int:
_ue_int:
		cli
		pushal

		movb	$EOI,%al	/* re-enable the device */
		outb	%al,$OCW1_2

		call	ue_intr

		popal
		sti
		iret

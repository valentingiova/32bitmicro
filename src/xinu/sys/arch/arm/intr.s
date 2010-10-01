/* intr.s - disable(), restore(), enable(), pause(), halt() */


#include <icu.s>

	.text
	.globl	_enable
	.globl	enable
	.globl	_disable
	.globl	disable
	.globl	_restore
	.globl	restore
	.globl	_pause
	.globl	_halt
	.globl	_getirmask

/*------------------------------------------------------------------------
 * Xtrap - trap entry
 *------------------------------------------------------------------------
 */
Xtrap:
/* 	call	_trap  */
	/* exception # */
	/* convert to IRQ # */

	/* issue global rearm to cards */
	bx lr

@#define	INT(I) \
@.globl	_Xint/**/I ;			\
@_Xint/**/I:	pushl	%ebp ;		\
@		movl	%esp,%ebp;	\
@		pushal ;		\
@		pushl	$I ;		\
@		jmp	Xtrap

/*------------------------------------------------------------------------
 * _Xint? - default exception and interrupt entry points
 *	NB: These must be contiguous
 *------------------------------------------------------------------------
 */

		.globl	_defevec
		.globl	defevec
_defevec:
defevec:	.word	0

/*****************************************************************************
INT(0);   INT(1);   INT(2);   INT(3);   INT(4);   INT(5);   INT(6);   INT(7);
INT(8);   INT(9);   INT(10);  INT(11);  INT(12);  INT(13);  INT(14);  INT(15);
INT(16);  INT(17);  INT(18);  INT(19);  INT(20);  INT(21);  INT(22);  INT(23);
INT(24);  INT(25);  INT(26);  INT(27);  INT(28);  INT(29);  INT(30);  INT(31);
INT(32);  INT(33);  INT(34);  INT(35);  INT(36);  INT(37);  INT(38);  INT(39);
INT(40);  INT(41);  INT(42);  INT(43);  INT(44);  INT(45);  INT(46);  INT(47);

		.globl	_defevec
_defevec:	.word	_Xint0
		.word	_Xint1
		.word	_Xint2
		.word	_Xint3
		.word	_Xint4
		.word	_Xint5
		.word	_Xint6
		.word	_Xint7
		.word	_Xint8
		.word	_Xint9
		.word	_Xint10
		.word	_Xint11
		.word	_Xint12
		.word	_Xint13
		.word	_Xint14
		.word	_Xint15
		.word	_Xint16
		.word	_Xint17
		.word	_Xint18
		.word	_Xint19
		.word	_Xint20
		.word	_Xint21
		.word	_Xint22
		.word	_Xint23
		.word	_Xint24
		.word	_Xint25
		.word	_Xint26
		.word	_Xint27
		.word	_Xint28
		.word	_Xint29
		.word	_Xint30
		.word	_Xint31
		.word	_Xint32
		.word	_Xint33
		.word	_Xint34
		.word	_Xint35
		.word	_Xint36
		.word	_Xint37
		.word	_Xint38
		.word	_Xint39
		.word	_Xint40
		.word	_Xint41
		.word	_Xint42
		.word	_Xint43
		.word	_Xint44
		.word	_Xint45
		.word	_Xint46
		.word	_Xint47
*****************************************************************************/
/*---------------------------------------------------------
 * pause: halt the processor until an interrupt occurs
 *---------------------------------------------------------
 */
_pause:
/* 	call _enable */
/* 	hlt */
	bx lr


/*---------------------------------------------------------
 * halt: do nothing forever
 *---------------------------------------------------------
 */
_halt:
/*	jmp _halt */
	bx lr

/*---------------------------------------------------------
 * enable all interrupts
 *---------------------------------------------------------
 */
_enable:
enable:
/* 	cli */
/* 	movw	_girmask,%ax */
/*	sti */
	bx lr


/*---------------------------------------------------------
 * disable(ps)    - disable interrupts, save old state in ps
 * STATWORD ps  (short *ps)
 *---------------------------------------------------------
 */
_disable:
disable:
/*	cli */
	/* clear _girmask bits for user */
/*	orw	_girmask,%ax */
	bx lr


/*---------------------------------------------------------
 * restore(ps)    - restore interrupts to value in ps
 * STATWORD ps    (short *ps)
 *---------------------------------------------------------
 */
_restore: 
restore: 
/*	cli */
/*	orw	_girmask,%ax */
	bx lr

/*------------------------------------------------------------------------
 * getirmask(ps)  - return current interrupt mask in ps
 *------------------------------------------------------------------------
 */
_getirmask:
	bx lr

/*------------------------------------------------------------------------
 * Xignore - ignore this exception
 *------------------------------------------------------------------------
 */
.globl	_Xignore
_Xignore:
	bx lr

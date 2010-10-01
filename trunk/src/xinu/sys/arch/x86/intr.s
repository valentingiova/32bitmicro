/* intr.s - disable(), restore(), enable(), pause(), halt() */


#include <icu.s>

	.text
	.globl	enable
	.globl	disable
	.globl	restore
	.globl	pause
	.globl	halt
	.globl	getirmask

/*------------------------------------------------------------------------
 * Xtrap - trap entry
 *------------------------------------------------------------------------
 */
Xtrap:
# com32 T
	movb	$0x02,%ah
	movb	$'T',%dl
	int	$0x21

	call	trap
	movb	$OCW1_2,%al
#	movw	$OCW1_2,%al
	outb	%al,$EOI
	popl	%eax		/* exception # */
	testl	$35,%eax
	jb	3f
	shrl	$5,%eax		/* convert to IRQ # */

	/* issue global rearm to cards */
	testl	$7,%eax
	ja	1f
	orl	$0x2f0,%eax	/* 0x2fX for IRQ 3-7 */
	movb	%bl,(%eax)
	jmp	3f
1:	testl	$9,%eax
	jz	2f
	testl	$15,%eax
	ja	3f
	orl	$0x6f0,%eax	/* 0x2f(X-8) for IRQ 10-15 */
	movb	%bl,(%eax)
	jmp	3f
2:	movb	%al,0x2f2	/* 0x2f2 for IRQ 9 */
3:
	popal
	leave
	iret

#define	INT(I) \
.globl	_Xint##I ;			\
_Xint##I:	pushl	%ebp ;		\
		movl	%esp,%ebp;	\
		pushal ;		\
		pushl	$I ;		\
		jmp	Xtrap

/*------------------------------------------------------------------------
 * _Xint? - default exception and interrupt entry points
 *	NB: These must be contiguous
 *------------------------------------------------------------------------
 */

INT(0);   INT(1);   INT(2);   INT(3);   INT(4);   INT(5);   INT(6);   INT(7); 
INT(8);   INT(9);   INT(10);  INT(11);  INT(12);  INT(13);  INT(14);  INT(15);
INT(16);  INT(17);  INT(18);  INT(19);  INT(20);  INT(21);  INT(22);  INT(23);
INT(24);  INT(25);  INT(26);  INT(27);  INT(28);  INT(29);  INT(30);  INT(31);
INT(32);  INT(33);  INT(34);  INT(35);  INT(36);  INT(37);  INT(38);  INT(39);
INT(40);  INT(41);  INT(42);  INT(43);  INT(44);  INT(45);  INT(46);  INT(47);

		.globl	defevec

defevec:	.long	_Xint0
		.long	_Xint1
		.long	_Xint2
		.long	_Xint3
		.long	_Xint4
		.long	_Xint5
		.long	_Xint6
		.long	_Xint7
		.long	_Xint8
		.long	_Xint9
		.long	_Xint10
		.long	_Xint11
		.long	_Xint12
		.long	_Xint13
		.long	_Xint14
		.long	_Xint15
		.long	_Xint16
		.long	_Xint17
		.long	_Xint18
		.long	_Xint19
		.long	_Xint20
		.long	_Xint21
		.long	_Xint22
		.long	_Xint23
		.long	_Xint24
		.long	_Xint25
		.long	_Xint26
		.long	_Xint27
		.long	_Xint28
		.long	_Xint29
		.long	_Xint30
		.long	_Xint31
		.long	_Xint32
		.long	_Xint33
		.long	_Xint34
		.long	_Xint35
		.long	_Xint36
		.long	_Xint37
		.long	_Xint38
		.long	_Xint39
		.long	_Xint40
		.long	_Xint41
		.long	_Xint42
		.long	_Xint43
		.long	_Xint44
		.long	_Xint45
		.long	_Xint46
		.long	_Xint47

/*---------------------------------------------------------
 * pause: halt the processor until an interrupt occurs
 *---------------------------------------------------------
 */
pause:
	call enable
	hlt
	ret


/*---------------------------------------------------------
 * halt: do nothing forever
 *---------------------------------------------------------
 */
halt:
	jmp halt
	ret

/*---------------------------------------------------------
 * enable all interrupts
 *---------------------------------------------------------
 */
enable:
	cli
	movw	girmask,%ax
	outb	%al,$IMR1
	shrw	$8,%ax
	outb	%al,$IMR2
	sti
	ret


/*---------------------------------------------------------
 * disable(ps)    - disable interrupts, save old state in ps
 * STATWORD ps  (short *ps)
 *---------------------------------------------------------
 */
disable:
	pushfl
	cli
	inb	$IMR2,%al
	shlw	$8,%ax
	inb	$IMR1,%al	
	notw	%ax		/* clear _girmask bits for user */
	orw	girmask,%ax
	notw	%ax
	movl	8(%esp),%edx	/* get PS pointer	*/
	movw	%ax,(%edx)	/* save old IR mask	*/
	movb	$0xff,%al
	outb	%al,$IMR2
	movb	$0xff,%al
	outb	%al,$IMR1
	popfl
	ret


/*---------------------------------------------------------
 * restore(ps)    - restore interrupts to value in ps
 * STATWORD ps    (short *ps)
 *---------------------------------------------------------
 */
restore: 
	pushfl
	cli
	movl	8(%esp),%edx
	movw	(%edx),%ax
	orw	girmask,%ax
	outb	%al,$IMR1
	shrw	$8,%ax
	outb	%al,$IMR2
	popfl
	ret

/*------------------------------------------------------------------------
 * getirmask(ps)  - return current interrupt mask in ps
 *------------------------------------------------------------------------
 */
getirmask:
	inb	$IMR2,%al
	shlw	$8,%ax
	inb	$IMR1,%al	
	movl	4(%esp),%edx
	movw	%ax,(%edx)
	ret

/*------------------------------------------------------------------------
 * Xignore - ignore this exception
 *------------------------------------------------------------------------
 */
.globl	_Xignore
_Xignore:
	iret

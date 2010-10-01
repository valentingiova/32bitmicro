/* ctxsw.s - ctxsw */

		.text
		.globl	_ctxsw
		.globl	ctxsw
newmask:	.word	0

/*------------------------------------------------------------------------
 * ctxsw -  call is ctxsw(&oldsp, &oldmask, &newsp, &newmask)
 *------------------------------------------------------------------------
 */
_ctxsw:
ctxsw:
/*		call	_disable */
/*		call	_restore */
		bx lr


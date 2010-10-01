/* kputc.c - kputc */

#include <conf.h>
#include <kernel.h>
#include <tty.h>

#ifdef __COM32__
int putchar_com32(int ch);
#endif
	
/*------------------------------------------------------------------------
 * kputc - do a synchronous kernel write to the console tty
 *------------------------------------------------------------------------
 */
int
kputc(dev, c)
int		dev;	/* fake dev-- always the console */
unsigned char	 c;
{
#ifdef __COM32__
	 putchar_com32(c);
#else
	kbmputc(&devtab[KBMON], c);
	comsputc(&devtab[SERIAL1], c);
#ifdef notdef
	if (devtab[CONSOLE].dvioblk)
		putc(CONSOLE, c);
	else /* no tty yet; put it on SERIAL0 */
		comsputc(&devtab[SERIAL0], c);
#endif
	return OK;
#endif
}

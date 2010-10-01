/* ----------------------------------------------------------------------- *
 *
 *
 * ----------------------------------------------------------------------- */

/*
 * init_com32.c
 *
 *
 */

#include <stdarg.h>
#include <com32.h>
#include "libmenu/com32io.h"
#include "libmenu/syslnx.h"

#define __intcall __com32.cs_intcall

com32sys_t inreg, outreg;	// Global register sets for use

static inline void memset_com32(void *buf, int ch, unsigned int len)
{
    asm volatile ("cld; rep; stosb":"+D" (buf), "+c"(len):"a"(ch):"memory");
}

void gotoxy(char row, char col, char page)
{
    REG_AH(inreg) = 0x02;
    REG_BH(inreg) = page;
    REG_DX(inreg) = (row << 8) + col;
    __intcall(0x10, &inreg, &outreg);
}

void init_com32(void)
{
    com32sys_t regs;

    /* switch to text mode */
    memset_com32(&regs, 0, sizeof regs);
    regs.eax.b[0] = 0x05;
    __com32.cs_intcall(0x22, &regs, NULL);
    
    /* cls */
    gotoxy(0, 0, 0);
    
    /* print message */
    puts_com32("XINU COM32");
}

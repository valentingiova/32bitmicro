/* create.c - create, newpid */
    
#include <conf.h>
#include <i386.h>
#include <kernel.h>
#include <proc.h>
#include <sem.h>
#include <mem.h>
#include <io.h>
#include <stdarg.h>

LOCAL newpid(void);
static unsigned long esp;

/*------------------------------------------------------------------------
 *  create  -  create a process to start running a procedure
 *------------------------------------------------------------------------
 */
SYSCALL create(int (*procaddr)(), int ssize, int priority, char *name,
		int nargs, ...)
{
	va_list		ap;
	unsigned long	savsp, *pushsp, topsp;
	STATWORD 	ps;    
	int		pid;		/* stores new process id	*/
	struct	pentry	*pptr;		/* pointer to proc. table entry */
	int		i;
	unsigned long	*saddr, *uarg;	/* stack address		*/
	unsigned long   *getstk();
	int		INITRET();
	int		cnargs;

	cnargs = nargs;
	va_start(ap, nargs);
	disable(ps);
	if (ssize < MINSTK)
		ssize = MINSTK;
	ssize = (int) roundew(ssize);
	if (((saddr = (unsigned long *)getstk(ssize)) ==
	    (unsigned long *)SYSERR ) ||
	    (pid=newpid()) == SYSERR || priority < 1 ) {
		restore(ps);
		va_end(ap);
		return SYSERR;
	}

	kprintf("ssize %d\n",ssize);
	
	numproc++;
	pptr = &proctab[pid];

	pptr->fildes[0] = 0;	/* stdin set to console */
	pptr->fildes[1] = 0;	/* stdout set to console */
	pptr->fildes[2] = 0;	/* stderr set to console */

	for (i=3; i < _NFILE; i++)	/* others set to unused */
		pptr->fildes[i] = FDFREE;

	pptr->pstate = PRSUSP;
	for (i=0 ; i<PNMLEN && (int)(pptr->pname[i]=name[i])!=0 ; i++)
		;
	pptr->pprio = priority;
	pptr->pbase = (long) saddr;
	pptr->pstklen = ssize;
	pptr->psem = 0;
	pptr->phasmsg = FALSE;
	pptr->plimit = pptr->pbase - ssize + sizeof (long);	
	pptr->pirmask[0] = 0;
	pptr->pnxtkin = BADPID;
	pptr->pdevs[0] = pptr->pdevs[1] = BADDEV;

	/* Bottom of stack */
	*saddr = MAGIC;
	savsp = topsp = (unsigned long)saddr;

	/* push arguments */
	pptr->pargs = nargs;
	uarg = saddr - nargs;
	saddr = uarg;	/* end of args for after the copy */
	for (; nargs > 0 ; nargs--)
		*uarg++ = va_arg(ap, unsigned long);
	*--saddr = (long)INITRET;	/* push on return address	*/
	
	*--saddr = pptr->paddr = (long)procaddr; /* where we "ret" to	*/
	*--saddr = savsp;		/* fake frame ptr for procaddr	*/
	savsp = (unsigned long) saddr;

/* this must match what ctxsw expects: flags, regs, old SP */
/* emulate 386 "pushal" instruction */
	*--saddr = 0;
	*--saddr = 0;	/* %eax */
	*--saddr = 0;	/* %ecx */
	*--saddr = 0;	/* %edx */
	*--saddr = 0;	/* %ebx */
	*--saddr = 0;	/* %esp; fill in below */
	pushsp = saddr;
	*--saddr = savsp;	/* %ebp */
	*--saddr = 0;		/* %esi */
	*--saddr = 0;		/* %edi */
	*pushsp = pptr->pesp = (unsigned long)saddr;

#ifdef DEBUG
	dumpstack(topsp, cnargs);
	dumppentry(pptr);
#endif
	restore(ps);
	va_end(ap);
	return pid;
}

/*------------------------------------------------------------------------
 * newpid  --  obtain a new (free) process id
 *------------------------------------------------------------------------
 */
LOCAL
newpid(void)
{
	int	pid;			/* process id to return		*/
	int	i;

	for (i=0 ; i<NPROC ; i++) {	/* check all NPROC slots	*/
		if ( (pid=nextproc--) <= 0)
			nextproc = NPROC-1;
		if (proctab[pid].pstate == PRFREE)
			return(pid);
	}
	return(SYSERR);
}

#ifdef DEBUG
/* passed the pointer to the regs in the process entry */
dumpstack(unsigned long	*saddr, int nargs)
{    
    kprintf("\nnew process stack frame at 0x%lx  nargs %d\n", saddr, nargs);
    kprintf("MAGIC    0x%lx",(unsigned long) *saddr);
    kprintf(" @ 0x%lx\n",(unsigned long) saddr);
    for (; nargs > 0 ; nargs--) {
	    kprintf("arg%d    0x%lx",nargs,(unsigned long) *--saddr);
	    kprintf(" @ 0x%lx\n",(unsigned long) saddr);
    }
    kprintf("INITRET  0x%lx",(unsigned long) *--saddr);
    kprintf(" @ 0x%lx\n",(unsigned long) saddr);
    kprintf("procaddr 0x%lx",(unsigned long) *--saddr);
    kprintf(" @ 0x%lx\n",(unsigned long) saddr);
    kprintf("savsp    0x%lx",(unsigned long) *--saddr);
    kprintf(" @ 0x%lx\n",(unsigned long) saddr);
    kprintf("flags    0x%lx",(unsigned long) *--saddr);
    kprintf(" @ 0x%lx\n",(unsigned long) saddr);
    kprintf("eax      0x%lx",(unsigned long) *--saddr);
    kprintf(" @ 0x%lx\n",(unsigned long) saddr);
    kprintf("ecx      0x%lx",(unsigned long) *--saddr);
    kprintf(" @ 0x%lx\n",(unsigned long) saddr);
    kprintf("edx      0x%lx",(unsigned long) *--saddr);
    kprintf(" @ 0x%lx\n",(unsigned long) saddr);
    kprintf("ebx      0x%lx",(unsigned long) *--saddr);
    kprintf(" @ 0x%lx\n",(unsigned long) saddr);
    kprintf("esp      0x%lx",(unsigned long) *--saddr);
    kprintf(" @ 0x%lx\n",(unsigned long) saddr);
    kprintf("ebp      0x%lx",(unsigned long) *--saddr);
    kprintf(" @ 0x%lx\n",(unsigned long) saddr);
    kprintf("esi      0x%lx",(unsigned long) *--saddr);
    kprintf(" @ 0x%lx\n",(unsigned long) saddr);
    kprintf("edi      0x%lx",(unsigned long) *--saddr);
    kprintf(" @ 0x%lx\n",(unsigned long) saddr);
}


dumppentry(struct pentry *ptr)
{
    kprintf("\npentry for process '%s'\n",ptr->pname);
    kprintf(" pesp:    0x%lx",(unsigned long) ptr->pesp);
    kprintf(" paddr:   0x%lx",(unsigned long) ptr->paddr);
    kprintf(" pstklen: 0x%lx\n",(unsigned long) ptr->pstklen);
}
#endif


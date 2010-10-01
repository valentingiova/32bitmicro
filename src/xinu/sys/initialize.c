/* initialize.c - nulluser, sizmem, sysinit */

#include <conf.h>
#include <i386.h>
#include <kernel.h>
#include <proc.h>
#include <sleep.h>
#include <mem.h>
#include <tty.h>
#include <io.h>
#include <network.h>

#ifdef __COM32__
unsigned int com32topmem;
int puts_com32(const char *s);
#endif

/* #define DETAIL */

#define	HOLESTART	((char *)(640 * 1024))
#define	HOLEEND		((char *)(1024 * 1024))

extern	int	main();			/* address of user's main prog	*/

extern	int	start();

LOCAL		sysinit();

/* Declarations of major kernel variables */

struct	pentry	proctab[NPROC]; /* process table			*/
int	nextproc;		/* next process slot to use in create	*/
struct	sentry	semaph[NSEM];	/* semaphore table			*/
int	nextsem;		/* next sempahore slot to use in screate*/
struct	qent	q[NQENT];	/* q table (see queue.c)		*/
int	nextqueue;		/* next slot in q structure to use	*/
char	*maxaddr;		/* max memory address (set by sizmem)	*/
#ifdef	NDEVS
struct	intmap	intmap[NDEVS];	/* interrupt dispatch table		*/
#endif
struct	mblock	memlist;	/* list of free memory blocks		*/
#ifdef	Ntty
struct  tty     tty[Ntty];	/* SLU buffers and mode control		*/
#endif

/* active system status */

int	numproc;		/* number of live user processes	*/
int	currpid;		/* id of currently running process	*/
int	lastpid;		/* id of last running process		*/
int	reboot = 0;		/* non-zero after first boot		*/

int	rdyhead,rdytail;	/* head/tail of ready list (q indicies)	*/
char	vers[100];		/* Xinu version printed at startup	*/
int	revision = REVISION;	/* the revision level			*/

/* These variables were defined in usrmain. */

int	sem;
int	pid1, pid2;
int	ptid;


/************************************************************************/
/***				NOTE:				      ***/
/***								      ***/
/***   This is where the system begins after the C environment has    ***/
/***   been established.  Interrupts are initially DISABLED, and      ***/
/***   must eventually be enabled explicitly.  This routine turns     ***/
/***   itself into the null process after initialization.  Because    ***/
/***   the null process must always remain ready to run, it cannot    ***/
/***   execute code that might cause it to be suspended, wait for a   ***/
/***   semaphore, or put to sleep, or exit.  In particular, it must   ***/
/***   not do I/O unless it uses kprintf for polled output.           ***/
/***								      ***/
/************************************************************************/

	
static int esp;
/*------------------------------------------------------------------------
 *  nulluser  -- initialize system and become the null process (id==0)
 *------------------------------------------------------------------------
 */
nulluser()				/* babysit CPU when no one home */
{
        int userpid;

#ifdef X__COM32__
	init_com32();
#endif
	initevec();

#ifdef X__COM32__
	puts_com32("initevec() done\n");
#endif
	
	sysinit();

#ifdef X__COM32__
	puts_com32("sysinit() done\n");
#endif
	
	/* associate CONSOLE with a tty */
	open(CONSOLE, KBMON, 0);
/*	open(CONSOLE, SERIAL0); */

	sprintf(vers, "Xinu Version %s", VERSION);
	kprintf("\n\n%s\n", vers);
	if (reboot++ < 1)
		kprintf("\n");
	else
		kprintf("   (reboot %d)\n", reboot);


	kprintf("%d bytes real mem\n",
		(unsigned long) maxaddr+1);
#ifdef DETAIL	
	kprintf("    %d", (unsigned long) 0);
	kprintf(" to %d\n", (unsigned long) (maxaddr) );
#endif	

	kprintf("%d bytes Xinu code\n",
		(unsigned long) ((unsigned long) &end - (unsigned long) start));
#ifdef DETAIL	
	kprintf("    %d", (unsigned long) start);
	kprintf(" to %d\n", (unsigned long) &end );
#endif

#ifdef DETAIL	
	kprintf("%d bytes user stack/heap space\n",
		(unsigned long) ((unsigned long) maxaddr - (unsigned long) &end));
	kprintf("    %d", (unsigned long) &end);
	kprintf(" to %d\n", (unsigned long) maxaddr);
#endif	
	
	kprintf("clock %sabled\n", clkruns == 1?"en":"dis");

/* !!!	enable();*/		/* enable interrupts */
	
	kprintf("interrupts enabled\n");

	/* create a process to execute the user's main program */
	userpid = create(main,INITSTK,INITPRIO,INITNAME,INITARGS);

	/* start the network */
	resume(create(netstart,NETSTK,NETPRI,NETNAM,NETARGC,userpid));
	while (TRUE)
		/* empty */;
}

/*------------------------------------------------------------------------
 *  sysinit  --  initialize all Xinu data structeres and devices
 *------------------------------------------------------------------------
 */
LOCAL
sysinit()
{
	static	long	currsp;
	int	i,j;
	struct	pentry	*pptr;
	struct	sentry	*sptr;
	struct	mblock	*mptr;

	numproc = 0;			/* initialize system variables */
	nextproc = NPROC-1;
	nextsem = NSEM-1;
	nextqueue = NPROC;		/* q[0..NPROC-1] are processes */

#ifdef X__COM32__
	puts_com32("sysinit()\n");
#endif
	
#ifdef __COM32__
	/* initialize free memory list */
	kprintf("com32topmem %d\n", (unsigned long) com32topmem);
	com32topmem = com32topmem - 1024*64; /* !!! we need some space fort this code */
	maxaddr =  (char*) com32topmem;
	kprintf("maxaddr     %d\n", (unsigned long) maxaddr);
	memlist.mnext = mptr = (struct mblock *) roundmb(&end);
	mptr->mnext = 0;
	mptr->mlen = (int) truncew((unsigned)maxaddr - (int)&end -
			NULLSTK);
#else
	/* initialize free memory list */
	/* PC version has to pre-allocate 640K-1024K "hole" */
	if (maxaddr+1 > HOLESTART) {
		memlist.mnext = mptr = (struct mblock *) roundmb(&end);
		mptr->mnext = (struct mblock *)HOLEEND;
		mptr->mlen = (int) truncew((unsigned) HOLESTART -
	     		 (unsigned)&end - 4);

		mptr = (struct mblock *) HOLEEND;
		mptr->mnext = 0;
		mptr->mlen = (int) truncew(maxaddr - HOLEEND - NULLSTK);
	} else {
		/* initialize free memory list */
		memlist.mnext = mptr = (struct mblock *) roundmb(&end);
		mptr->mnext = 0;
		mptr->mlen = (int) truncew((unsigned)maxaddr - (int)&end -
			NULLSTK);
	}
#endif
	
#ifdef X__COM32__
	puts_com32("sysinit() free memory list done\n");
#endif
	
	for (i=0 ; i<NPROC ; i++)	/* initialize process table */
		proctab[i].pstate = PRFREE;

#ifdef X__COM32__
	puts_com32("sysinit() proctab done\n");
#endif
	
	pptr = &proctab[NULLPROC];	/* initialize null process entry */
	pptr->pstate = PRCURR;
	for (j=0; j<7; j++)
		pptr->pname[j] = "prnull"[j];
	pptr->plimit = (WORD)(maxaddr + 1) - NULLSTK;
	pptr->pbase = (WORD) maxaddr - 3;
	pptr->pesp = pptr->pbase-4;	/* for stkchk; rewritten before used */
	*( (int *)pptr->pbase ) = MAGIC;
	pptr->paddr = (WORD) nulluser;
	pptr->pargs = 0;
	pptr->pprio = 0;
	currpid = NULLPROC;

	for (i=0 ; i<NSEM ; i++) {	/* initialize semaphores */
		(sptr = &semaph[i])->sstate = SFREE;
		sptr->sqtail = 1 + (sptr->sqhead = newqueue());
	}

	rdytail = 1 + (rdyhead=newqueue());/* initialize ready list */

#ifdef X__COM32__
	puts_com32("sysinit() semaphores done\n");
#endif
	
#ifdef	MEMMARK
	_mkinit();			/* initialize memory marking */
#ifdef __COM32__
	puts_com32("sysinit()  memory marking done\n");
#endif
#endif

#ifdef	RTCLOCK
	clkinit();			/* initialize r.t.clock	*/
#ifdef __COM32__
	puts_com32("sysinit() rtc done\n");
#endif
#endif

#ifdef NDEVS
	for ( i=0 ; i<NDEVS ; i++ ) {
	    init(i);
	}
#ifdef __COM32__
	puts_com32("sysinit() devs done\n");
#endif	
#endif

#ifdef	NNETS
	netinit();
#ifdef __COM32__
	puts_com32("sysinit() netinit() done\n");
#endif
#endif

	return(OK);
}

_stop(s)
char	*s;
{
	kprintf("%s\n", s);
	kprintf("looping... press reset\n");
	while(1)
		/* empty */;
}


#define	NBPG	4096

/*------------------------------------------------------------------------
 * sizmem - return memory size (in pages)
 *------------------------------------------------------------------------
 */
long
sizmem()
{
	volatile unsigned char	*ptr;
	unsigned char		*start, stmp, tmp;
	int			npages;

	npages = ((int)&end + NBPG)/NBPG;	/* # pages of text+BSS */
	ptr = start = (char *)(npages*NBPG);
	stmp = *start;
	kprintf("sizemem text+BSS npages %i\n", npages);
	while (1) {
		int i, bad=0;
#ifdef __COM32__
		if ( (unsigned int) ptr > com32topmem )
			break;
#else
		/* this is destructive way of sizing up memory */
		tmp = *ptr;
		*ptr = 0xA5;
		if (*ptr != 0xA5)
			break;
#endif
		++npages;
		ptr += NBPG;
		if ((char *)ptr == HOLESTART) {	/* skip I/O pages */
			npages += (1024-640)/4;
			ptr = HOLEEND;
		}
	}
	kprintf("sizemem found npages %i\n", npages);
	return npages;	/* for lint */
}

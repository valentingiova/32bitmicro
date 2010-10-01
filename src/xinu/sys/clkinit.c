/* clkinit.c - clkinit, updateleds, dog_timeout */

#include <conf.h>
#include <kernel.h>
#include <sleep.h>
#include <cpu.addrs.h>    
#include <i386.h>

#ifdef X__COM32__
int puts_com32(const char *s);
#endif

/* Intel 8254-2 clock chip constants */

#define	CLOCKBASE	0x40		/* I/O base port of clock chip	*/
#define	CLOCK0		CLOCKBASE
#define	CLKCNTL		(CLOCKBASE+3)	/* chip CSW I/O port		*/

#define	CLKHZ		1190		/* kHz 				*/
#define	DIVIDER		(CLKHZ * 10)	/* 10ms interrupt rate		*/
    
/* real-time clock variables and sleeping process queue pointers	*/
    
#ifdef	RTCLOCK
int	count6;			/* counts in 60ths of a second 6-0	*/
int	count10;		/* counts in 10ths of second 10-0	*/
unsigned	long	ctr100;	/* counts in 100ths of second 0-INF	*/
extern long	cnt100;		/* counts in 100ths of second 10-0	*/
int	clmutex;		/* mutual exclusion for time-of-day	*/
long	clktime;		/* current time in seconds since 1/1/70	*/
int     defclk;			/* non-zero, then deferring clock count */
int     clkdiff;		/* deferred clock ticks			*/
int     slnempty;		/* FALSE if the sleep queue is empty	*/
int     *sltop;			/* address of key part of top entry in	*/
				/* the sleep queue if slnonempty==TRUE	*/
int     clockq;			/* head of queue of sleeping processes  */
int	preempt;		/* preemption counter.	Current process */
				/* is preempted when it reaches zero;	*/
#ifdef	RTCLOCK
				/* set in resched; counts in ticks	*/
int	clkruns;		/* set TRUE iff clock exists by setclkr	*/
#else
int	clkruns = FALSE;	/* no clock configured; be sure sleep	*/
#endif				/*   doesn't wait forever		*/

void compute_delay(void);

/*
 *------------------------------------------------------------------------
 * clkinit - initialize the clock and sleep queue (called at startup)
 *------------------------------------------------------------------------
 */
int
clkinit(void)
{
	int clkint();

#ifdef X__COM32__
	puts_com32("clkinit() begin");
#endif
	
	set_evec(IRQBASE, clkint);

#ifdef X__COM32__
	puts_com32("clkinit() set_evec done");
#endif
	
	clkruns = 1;
	clockq = newqueue();
	preempt = QUANTUM;		/* initial time quantum		*/
	
#ifdef X__COM32__
	puts_com32("clkinit() quantum done");
#endif
	
	compute_delay();

#ifdef X__COM32__
	puts_com32("clkinit() compute_delay done");
#endif
	
#ifdef I386
	/*  set to: timer 0, 16-bit counter, rate generator mode,
		counter is binary */
	outb(CLKCNTL, 0x34);
#ifdef X__COM32__
	puts_com32("clkinit() outb CLKCNTL done");
#endif
	/* must write LSB first, then MSB */
	outb(CLOCK0, (char)DIVIDER);
	outb(CLOCK0, DIVIDER>>8);

#ifdef X__COM32__
	puts_com32("clkinit() outb DIVIDER done");
#endif
	
#endif
	return OK;
}
#endif

void
compute_delay(void)
{
	extern unsigned int	cpudelay;
	unsigned int		tcount;
	unsigned int		dlow, dhigh;

	cpudelay = dlow = 1;
	tcount = 0;

#ifdef X__COM32__
	puts_com32("compute_delay() begin");
#endif
	/* find high bound for cpudelay */

	while (tcount < 1190) {
		dlow = cpudelay;
		dhigh = cpudelay = 2 * cpudelay;
#ifdef I386
		/* set counter to max */
		outb(CLKCNTL, 0x34);
		outb(CLOCK0, 0xff);	/* LSB */
		outb(CLOCK0, 0xff);	/* MSB */
#ifdef X__COM32__
		puts_com32("compute_delay() set counter to max done");
#endif
#endif
		delay(100);	/* 1 ms */

#ifdef X__COM32__
		puts_com32("compute_delay() delay done");
#endif
		
#ifdef I386
		outb(CLKCNTL, 0x0);	/* latch timer 0 */
		tcount = inb(CLOCK0);
		tcount = (inb(CLOCK0) << 8) | tcount;
		tcount = ((unsigned int)0xffff) - tcount;
#ifdef X__COM32__
		puts_com32("compute_delay() latch timer 0 done");
#endif
#endif
		
	}

	while (dlow < dhigh) {

		cpudelay = (dlow + dhigh) / 2;
#ifdef I386
		/* set counter to max */
		outb(CLKCNTL, 0x34);
		outb(CLOCK0, 0xff);	/* LSB */
		outb(CLOCK0, 0xff);	/* MSB */
#endif
		delay(100);	/* 1 ms */
#ifdef I386
		outb(CLKCNTL, 0x0);	/* latch timer 0 */
		tcount = inb(CLOCK0);
		tcount = (inb(CLOCK0) << 8) | tcount;
		tcount = ((unsigned int)0xffff) - tcount;
#endif

		if (tcount == CLKHZ)
			break;		/* exact match */
		if (tcount < CLKHZ)	/* too small */
			cpudelay = dlow = cpudelay + 1;
		else	/* too big */
			dhigh = cpudelay - 1;

	}

#ifdef X__COM32__
	puts_com32("compute_delay() end");
#endif
}


#ifdef notyet
/*
 * dog_timeout -- called when the watchdog timer determines that
 * interrupts have been disabled for too long
 */
void
dog_timeout(void)
{
    STATWORD ps;

    disable(ps);
    kprintf("\n\nWatchdog timeout!! -- interrupts disabled too long.\n");
    ret_mon();
    restore(ps);
    return;
}
#endif /* not yet */

int
clktest(void)
{
	kprintf("from clkint, ctr100 %d\n", ctr100);
}

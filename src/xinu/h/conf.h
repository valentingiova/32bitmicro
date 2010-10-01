/* conf.h (GENERATED FILE; DO NOT EDIT) */

#define	NULLPTR	(char *)0

/* Device table declarations */
struct	devsw	{			/* device table entry */
	int	dvnum;
	char	*dvname;
	int	(*dvinit)(struct devsw *);
	int	(*dvopen)(struct devsw *, void *, void *);
	int	(*dvclose)(struct devsw *);
	int	(*dvread)(struct devsw *, char *, unsigned);
	int	(*dvwrite)(struct devsw *, unsigned char *, unsigned);
	int	(*dvseek)(struct devsw *, long);
	int	(*dvgetc)(struct devsw *);
	int	(*dvputc)(struct devsw *, unsigned char);
	int	(*dvcntl)(struct devsw *, int, void *, void *);
	void	*dvcsr;
	int	dvivec;
	int	dvovec;
	void	(*dviint)(struct devsw *, unsigned char);
	void	(*dvoint)(struct devsw *);
	void	*dvioblk;
	int	dvminor;
	};

extern	struct	devsw devtab[];		/* one entry per device */


/* Device name definitions */

#define	KBMON       0			/* type kbmon    */
#define	SERIAL0     1			/* type serial   */
#define	SERIAL1     2			/* type serial   */
#define	CONSOLE     3			/* type tty      */
#define	TTY0        4			/* type tty      */
#define	TTY1        5			/* type tty      */
#define	TTY2        6			/* type tty      */
#define	ETHER       7			/* type eth      */
#define	UDP         8			/* type dgm      */
#define	DGRAM0      9			/* type dg       */
#define	DGRAM1      10			/* type dg       */
#define	DGRAM2      11			/* type dg       */
#define	DGRAM3      12			/* type dg       */
#define	DGRAM4      13			/* type dg       */
#define	DGRAM5      14			/* type dg       */
#define	DGRAM6      15			/* type dg       */
#define	DGRAM7      16			/* type dg       */
#define	DGRAM8      17			/* type dg       */
#define	DGRAM9      18			/* type dg       */
#define	DGRAMA      19			/* type dg       */
#define	DGRAMB      20			/* type dg       */
#define	DGRAMC      21			/* type dg       */
#define	DGRAMD      22			/* type dg       */
#define	DGRAME      23			/* type dg       */
#define	DGRAMF      24			/* type dg       */
#define	TCP         25			/* type tcpm     */
#define	TCP0        26			/* type tcp      */
#define	TCP1        27			/* type tcp      */
#define	TCP2        28			/* type tcp      */
#define	TCP3        29			/* type tcp      */
#define	TCP4        30			/* type tcp      */
#define	TCP5        31			/* type tcp      */
#define	TCP6        32			/* type tcp      */
#define	TCP7        33			/* type tcp      */
#define	TCP8        34			/* type tcp      */
#define	TCP9        35			/* type tcp      */
#define	TCPA        36			/* type tcp      */
#define	TCPB        37			/* type tcp      */
#define	TCPC        38			/* type tcp      */
#define	TCPD        39			/* type tcp      */
#define	TCPE        40			/* type tcp      */
#define	TCPF        41			/* type tcp      */
#define	RFILSYS     42			/* type rfm      */
#define	RFILE1      43			/* type rf       */
#define	RFILE2      44			/* type rf       */
#define	RFILE3      45			/* type rf       */
#define	RFILE4      46			/* type rf       */
#define	NAMESPACE   47			/* type nam      */

/* Control block sizes */

#define	Nkbmon	1
#define	Nserial	2
#define	Ntty	4
#define	Neth	1
#define	Ndgm	1
#define	Ndg	16
#define	Ntcpm	1
#define	Ntcp	16
#define	Nrfm	1
#define	Nrf	4
#define	Nnam	1

#define	NDEVS	48

/* Declarations of I/O routines referenced */

extern	int	kbminit(struct devsw *);
extern	int	noopen(struct devsw *, void *, void *);
extern	int	noclose(struct devsw *);
extern	int	kbmread(struct devsw *, char *, unsigned);
extern	int	kbmwrite(struct devsw *, unsigned char *, unsigned);
extern	int	noseek(struct devsw *, long);
extern	int	kbmcntl(struct devsw *, int, void *, void *);
extern	int	kbmgetc(struct devsw *);
extern	int	kbmputc(struct devsw *, unsigned char);
extern	void	kbmint(struct devsw *, unsigned char);
extern	void	nooint(struct devsw *);
extern	int	cominit(struct devsw *);
extern	int	noread(struct devsw *, char *, unsigned);
extern	int	comwrite(struct devsw *, unsigned char *, unsigned);
extern	int	comcntl(struct devsw *, int, void *, void *);
extern	int	comgetc(struct devsw *);
extern	int	computc(struct devsw *, unsigned char);
extern	void	comint(struct devsw *, unsigned char);
extern	int	ttyinit(struct devsw *);
extern	int	ttyopen(struct devsw *, void *, void *);
extern	int	ttyread(struct devsw *, char *, unsigned);
extern	int	ttywrite(struct devsw *, unsigned char *, unsigned);
extern	int	ttycntl(struct devsw *, int, void *, void *);
extern	int	ttygetc(struct devsw *);
extern	int	ttyputc(struct devsw *, unsigned char);
extern	void	ttyiin(struct devsw *, unsigned char);
extern	void	ttyoin(struct devsw *);
extern	int	ue_init(struct devsw *);
extern	int	ue_write(struct devsw *, unsigned char *, unsigned);
extern	int	ue_cntl(struct devsw *, int, void *, void *);
extern	int	nogetc(struct devsw *);
extern	int	noputc(struct devsw *, unsigned char);
extern	void	ue_intr(struct devsw *);
extern	int	ionull(struct devsw *);
extern	int	dgmopen(struct devsw *, void *, void *);
extern	int	nowrite(struct devsw *, unsigned char *, unsigned);
extern	int	dgmcntl(struct devsw *, int, void *, void *);
extern	void	noiint(struct devsw *, unsigned char);
extern	int	dginit(struct devsw *);
extern	int	dgclose(struct devsw *);
extern	int	dgread(struct devsw *, char *, unsigned);
extern	int	dgwrite(struct devsw *, unsigned char *, unsigned);
extern	int	dgcntl(struct devsw *, int, void *, void *);
extern	int	tcpmopen(struct devsw *, void *, void *);
extern	int	tcpmcntl(struct devsw *, int, void *, void *);
extern	int	tcpinit(struct devsw *);
extern	int	tcpclose(struct devsw *);
extern	int	tcpread(struct devsw *, char *, unsigned);
extern	int	tcpwrite(struct devsw *, unsigned char *, unsigned);
extern	int	tcpcntl(struct devsw *, int, void *, void *);
extern	int	tcpgetc(struct devsw *);
extern	int	tcpputc(struct devsw *, unsigned char);
extern	void	ioerr(void);
extern	int	rfopen(struct devsw *, void *, void *);
extern	int	rfcntl(struct devsw *, int, void *, void *);
extern	int	rfinit(struct devsw *);
extern	int	rfclose(struct devsw *);
extern	int	rfread(struct devsw *, char *, unsigned);
extern	int	rfwrite(struct devsw *, unsigned char *, unsigned);
extern	int	rfseek(struct devsw *, long);
extern	int	rfgetc(struct devsw *);
extern	int	rfputc(struct devsw *, unsigned char);
extern	int	naminit(struct devsw *);
extern	int	namopen(struct devsw *, void *, void *);
extern	int	nocntl(struct devsw *, int, void *, void *);


/* Configuration and Size Constants */

#define	LITTLE_ENDIAN	0x1234
#define	BIG_ENDIAN	0x4321

#define	BYTE_ORDER	LITTLE_ENDIAN

#define	CONTACT     "dls@purdue.edu"	/* administrative contact	*/
#define	LOCATION    "Xinu Lab"		/* Host's physical location	*/

#define	NPROC	    50			/* number of user processes	*/
#define	NSEM	    200			/* number of semaphores		*/
#define	MEMMARK				/* define if memory marking used*/
#define	RTCLOCK				/* now have RTC support		*/
#define	STKCHK				/* resched checks stack overflow*/
#define	NETDAEMON			/* Ethernet network daemon runs	*/
#define OSPF				/* define if using OSPF		*/
#ifdef notdef
#define NETMON				/* define for network monitor	*/
#endif
#define	SNMP				/* define for SNMP & MIB	*/
#define RIP				/* define if using RIP		*/
#define MULTICAST			/* define if using multicasting	*/

#ifdef	OSPF
#define	MULTICAST			/* OSPF uses multicasting	*/
#endif	/* OSPF */

#define	IPADDR1	"10.3.0.3"		/* interface 1 IP address	*/
#define	DEFRTR	"10.3.0.1"		/* default router		*/
#define	TSERVER	"10.3.0.1:37"		/* Time server address		*/
#define	RSERVER	"10.3.0.1:2001"		/* Remote file server address	*/
#define	NSERVER	"10.3.0.1:53"		/* Domain Name server address	*/
#define	LOGHOST	"10.3.0.1:514"		/* syslog server address	*/

#define	BINGID	9			/* Othernet simlated net param. */

#define	SMALLMTU	400		/* for OTHER2; sim. small MTU	*/

#define	BPMAXB	8192			/* max buffer size for mkpool	*/
#define BPMAXN	128			/* max # buffers in a buf pool	*/

#define	TCPSBS	4096			/* TCP send buffer sizes	*/
#define	TCPRBS	8192			/* TCP receive buffer sizes	*/

#define	NPORTS	100

#define	TIMERGRAN	1		/* timer granularity, secs/10	*/

#define	NAREA		1		/* max number of OSPF Areas	*/

#ifndef	Noth
#define	Noth	0
#endif	/* !Noth */
#ifndef	Ndg
#define	Ndg	0
#endif

/* conf.c (GENERATED FILE; DO NOT EDIT) */

#include <conf.h>

/* device independent I/O switch */

struct	devsw	devtab[NDEVS] = {

/*  Format of entries is:
device-number, device-name,
init, open, close,
read, write, seek,
getc, putc, cntl,
device-csr-address, input-vector, output-vector,
iint-handler, oint-handler, control-block, minor-device,
*/

/*  KBMON  is kbmon  */

0, "KBMON",
kbminit, noopen, noclose,
kbmread, kbmwrite, noseek,
kbmgetc, kbmputc, kbmcntl,
(void *)0000000, 0041, 0041,
kbmint, nooint, NULLPTR, 0,

/*  SERIAL0  is serial  */

1, "SERIAL0",
cominit, noopen, noclose,
noread, comwrite, noseek,
comgetc, computc, comcntl,
(void *)0001770, 0044, 0044,
comint, nooint, NULLPTR, 0,

/*  SERIAL1  is serial  */

2, "SERIAL1",
cominit, noopen, noclose,
noread, comwrite, noseek,
comgetc, computc, comcntl,
(void *)0001370, 0043, 0043,
comint, nooint, NULLPTR, 1,

/*  CONSOLE  is tty  */

3, "CONSOLE",
ttyinit, ttyopen, noclose,
ttyread, ttywrite, noseek,
ttygetc, ttyputc, ttycntl,
(void *)0000000, 0000, 0000,
ttyiin, ttyoin, NULLPTR, 0,

/*  TTY0  is tty  */

4, "TTY0",
ttyinit, ttyopen, noclose,
ttyread, ttywrite, noseek,
ttygetc, ttyputc, ttycntl,
(void *)0000000, 0000, 0000,
ttyiin, ttyoin, NULLPTR, 1,

/*  TTY1  is tty  */

5, "TTY1",
ttyinit, ttyopen, noclose,
ttyread, ttywrite, noseek,
ttygetc, ttyputc, ttycntl,
(void *)0000000, 0000, 0000,
ttyiin, ttyoin, NULLPTR, 2,

/*  TTY2  is tty  */

6, "TTY2",
ttyinit, ttyopen, noclose,
ttyread, ttywrite, noseek,
ttygetc, ttyputc, ttycntl,
(void *)0000000, 0000, 0000,
ttyiin, ttyoin, NULLPTR, 3,

/*  ETHER  is eth  */

7, "ETHER",
ue_init, noopen, noclose,
noread, ue_write, noseek,
nogetc, noputc, ue_cntl,
(void *)0001100, 0052, 0052,
ue_intr, ue_intr, NULLPTR, 0,

/*  UDP  is dgm  */

8, "UDP",
ionull, dgmopen, noclose,
noread, nowrite, noseek,
nogetc, noputc, dgmcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 0,

/*  DGRAM0  is dg  */

9, "DGRAM0",
dginit, noopen, dgclose,
dgread, dgwrite, noseek,
nogetc, noputc, dgcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 0,

/*  DGRAM1  is dg  */

10, "DGRAM1",
dginit, noopen, dgclose,
dgread, dgwrite, noseek,
nogetc, noputc, dgcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 1,

/*  DGRAM2  is dg  */

11, "DGRAM2",
dginit, noopen, dgclose,
dgread, dgwrite, noseek,
nogetc, noputc, dgcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 2,

/*  DGRAM3  is dg  */

12, "DGRAM3",
dginit, noopen, dgclose,
dgread, dgwrite, noseek,
nogetc, noputc, dgcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 3,

/*  DGRAM4  is dg  */

13, "DGRAM4",
dginit, noopen, dgclose,
dgread, dgwrite, noseek,
nogetc, noputc, dgcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 4,

/*  DGRAM5  is dg  */

14, "DGRAM5",
dginit, noopen, dgclose,
dgread, dgwrite, noseek,
nogetc, noputc, dgcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 5,

/*  DGRAM6  is dg  */

15, "DGRAM6",
dginit, noopen, dgclose,
dgread, dgwrite, noseek,
nogetc, noputc, dgcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 6,

/*  DGRAM7  is dg  */

16, "DGRAM7",
dginit, noopen, dgclose,
dgread, dgwrite, noseek,
nogetc, noputc, dgcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 7,

/*  DGRAM8  is dg  */

17, "DGRAM8",
dginit, noopen, dgclose,
dgread, dgwrite, noseek,
nogetc, noputc, dgcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 8,

/*  DGRAM9  is dg  */

18, "DGRAM9",
dginit, noopen, dgclose,
dgread, dgwrite, noseek,
nogetc, noputc, dgcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 9,

/*  DGRAMA  is dg  */

19, "DGRAMA",
dginit, noopen, dgclose,
dgread, dgwrite, noseek,
nogetc, noputc, dgcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 10,

/*  DGRAMB  is dg  */

20, "DGRAMB",
dginit, noopen, dgclose,
dgread, dgwrite, noseek,
nogetc, noputc, dgcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 11,

/*  DGRAMC  is dg  */

21, "DGRAMC",
dginit, noopen, dgclose,
dgread, dgwrite, noseek,
nogetc, noputc, dgcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 12,

/*  DGRAMD  is dg  */

22, "DGRAMD",
dginit, noopen, dgclose,
dgread, dgwrite, noseek,
nogetc, noputc, dgcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 13,

/*  DGRAME  is dg  */

23, "DGRAME",
dginit, noopen, dgclose,
dgread, dgwrite, noseek,
nogetc, noputc, dgcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 14,

/*  DGRAMF  is dg  */

24, "DGRAMF",
dginit, noopen, dgclose,
dgread, dgwrite, noseek,
nogetc, noputc, dgcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 15,

/*  TCP  is tcpm  */

25, "TCP",
ionull, tcpmopen, noclose,
noread, nowrite, noseek,
nogetc, noputc, tcpmcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 0,

/*  TCP0  is tcp  */

26, "TCP0",
tcpinit, noopen, tcpclose,
tcpread, tcpwrite, noseek,
tcpgetc, tcpputc, tcpcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 0,

/*  TCP1  is tcp  */

27, "TCP1",
tcpinit, noopen, tcpclose,
tcpread, tcpwrite, noseek,
tcpgetc, tcpputc, tcpcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 1,

/*  TCP2  is tcp  */

28, "TCP2",
tcpinit, noopen, tcpclose,
tcpread, tcpwrite, noseek,
tcpgetc, tcpputc, tcpcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 2,

/*  TCP3  is tcp  */

29, "TCP3",
tcpinit, noopen, tcpclose,
tcpread, tcpwrite, noseek,
tcpgetc, tcpputc, tcpcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 3,

/*  TCP4  is tcp  */

30, "TCP4",
tcpinit, noopen, tcpclose,
tcpread, tcpwrite, noseek,
tcpgetc, tcpputc, tcpcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 4,

/*  TCP5  is tcp  */

31, "TCP5",
tcpinit, noopen, tcpclose,
tcpread, tcpwrite, noseek,
tcpgetc, tcpputc, tcpcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 5,

/*  TCP6  is tcp  */

32, "TCP6",
tcpinit, noopen, tcpclose,
tcpread, tcpwrite, noseek,
tcpgetc, tcpputc, tcpcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 6,

/*  TCP7  is tcp  */

33, "TCP7",
tcpinit, noopen, tcpclose,
tcpread, tcpwrite, noseek,
tcpgetc, tcpputc, tcpcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 7,

/*  TCP8  is tcp  */

34, "TCP8",
tcpinit, noopen, tcpclose,
tcpread, tcpwrite, noseek,
tcpgetc, tcpputc, tcpcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 8,

/*  TCP9  is tcp  */

35, "TCP9",
tcpinit, noopen, tcpclose,
tcpread, tcpwrite, noseek,
tcpgetc, tcpputc, tcpcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 9,

/*  TCPA  is tcp  */

36, "TCPA",
tcpinit, noopen, tcpclose,
tcpread, tcpwrite, noseek,
tcpgetc, tcpputc, tcpcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 10,

/*  TCPB  is tcp  */

37, "TCPB",
tcpinit, noopen, tcpclose,
tcpread, tcpwrite, noseek,
tcpgetc, tcpputc, tcpcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 11,

/*  TCPC  is tcp  */

38, "TCPC",
tcpinit, noopen, tcpclose,
tcpread, tcpwrite, noseek,
tcpgetc, tcpputc, tcpcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 12,

/*  TCPD  is tcp  */

39, "TCPD",
tcpinit, noopen, tcpclose,
tcpread, tcpwrite, noseek,
tcpgetc, tcpputc, tcpcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 13,

/*  TCPE  is tcp  */

40, "TCPE",
tcpinit, noopen, tcpclose,
tcpread, tcpwrite, noseek,
tcpgetc, tcpputc, tcpcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 14,

/*  TCPF  is tcp  */

41, "TCPF",
tcpinit, noopen, tcpclose,
tcpread, tcpwrite, noseek,
tcpgetc, tcpputc, tcpcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 15,

/*  RFILSYS  is rfm  */

42, "RFILSYS",
ioerr, rfopen, noclose,
noread, nowrite, noseek,
nogetc, noputc, rfcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 0,

/*  RFILE1  is rf  */

43, "RFILE1",
rfinit, noopen, rfclose,
rfread, rfwrite, rfseek,
rfgetc, rfputc, rfcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 0,

/*  RFILE2  is rf  */

44, "RFILE2",
rfinit, noopen, rfclose,
rfread, rfwrite, rfseek,
rfgetc, rfputc, rfcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 1,

/*  RFILE3  is rf  */

45, "RFILE3",
rfinit, noopen, rfclose,
rfread, rfwrite, rfseek,
rfgetc, rfputc, rfcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 2,

/*  RFILE4  is rf  */

46, "RFILE4",
rfinit, noopen, rfclose,
rfread, rfwrite, rfseek,
rfgetc, rfputc, rfcntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 3,

/*  NAMESPACE  is nam  */

47, "NAMESPACE",
naminit, namopen, noclose,
noread, nowrite, noseek,
nogetc, noputc, nocntl,
(void *)0000000, 0000, 0000,
noiint, nooint, NULLPTR, 0
	};

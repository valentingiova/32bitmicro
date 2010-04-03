#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "lpc17xx.h"
#include "system_LPC17xx.h"
#include "lpc17xx_uart.h"
#include "lpc17xx_rtc.h"
#include "monitor.h"
#include "integer.h"
#include "diskio.h"
#include "ff.h"

#define VERSION_STRING 


char linebuf[120];			/* Console input buffer */

DWORD acc_size;				/* Work register for fs command */
WORD acc_files, acc_dirs;
FILINFO Finfo;
#if _USE_LFN
char Lfname[512];
#endif

FATFS Fatfs[_DRIVES];		/* File system object for each logical drive */
FIL File1, File2;			/* File objects */
DIR Dir;					/* Directory object */

//BYTE Buff[16384] __attribute__ ((aligned (4))) ;		/* Working buffer */
static BYTE *Buff = (BYTE *)0x2007C000;	 
static UINT blen = 16*1024;

volatile UINT Timer = 0;		/* Performance timer (1kHz increment) */

/* LED indicator */
#define LED1ON()  do {LPC_GPIO1 -> FIOSET |= (1<<28);}while (0)
#define LED1OFF() do {LPC_GPIO1 -> FIOCLR |= (1<<28);}while (0)

/* SysTick Interrupt Handler (1ms)    */
void SysTick_Handler (void) 
{           
	static DWORD pres, flip, prescale_disk_io;

	Timer++;

	if ( pres++ >= 500 ) {
		pres = 0;
		if (flip) LED1ON(); 
		else LED1OFF();
		flip = !flip;
	}

	// Disk timer process to be called every 10 ms
	if ( prescale_disk_io++ >=10 ) {
		prescale_disk_io = 0;
//		disk_timerproc(); /* <- Disk timer process to be called every 10 ms */
	}
}

/*---------------------------------------------------------*/
/* User Provided RTC Function for FatFs module             */
/*---------------------------------------------------------*/
/* This is a real time clock service to be called from     */
/* FatFs module. Any valid time must be returned even if   */
/* the system does not support an RTC.                     */
/* This function is not required in read-only cfg.         */
DWORD get_fattime ()
{
	RTCTime rtc;

	/* Get local time */
	rtc_gettime(&rtc);

	/* Pack date and time into a DWORD variable */
	return	  ((DWORD)(rtc.RTC_Year - 1980) << 25)
			| ((DWORD)rtc.RTC_Mon << 21)
			| ((DWORD)rtc.RTC_Mday << 16)
			| ((DWORD)rtc.RTC_Hour << 11)
			| ((DWORD)rtc.RTC_Min << 5)
			| ((DWORD)rtc.RTC_Sec >> 1);
}


static void put_rc (FRESULT rc)
{

	static const char str[] =
		"OK\0" "DISK_ERR\0" "INT_ERR\0" "NOT_READY\0" "NO_FILE\0" "NO_PATH\0"
		"INVALID_NAME\0" "DENIED\0" "EXIST\0" "INVALID_OBJECT\0" "WRITE_PROTECTED\0"
		"INVALID_DRIVE\0" "NOT_ENABLED\0" "NO_FILE_SYSTEM\0" "MKFS_ABORTED\0" "TIMEOUT\0";
	
	const char *p;
	FRESULT i;

	for (p = str, i = FR_OK /* 0 */; 
	i != rc && *p; 
	i++) {
		while(*p++);
	}
	xprintf("rc=%u FR_%s\n", (UINT)rc, p);
}

/*--------------------------------------------------------------------------*/
/* Monitor                                                                  */
/*--------------------------------------------------------------------------*/
static
FRESULT scan_files (
	char* path		/* Pointer to the path name working buffer */
)
{
	DIR dirs;
	FRESULT res;
	BYTE i;
	char *fn;


	if ((res = f_opendir(&dirs, path)) == FR_OK) {
		i = strlen(path);
		while (((res = f_readdir(&dirs, &Finfo)) == FR_OK) && Finfo.fname[0]) {
			if (Finfo.fname[0] == '.') continue;
#if _USE_LFN
			fn = *Finfo.lfname ? Finfo.lfname : Finfo.fname;
#else
			fn = Finfo.fname;
#endif
			if (Finfo.fattrib & AM_DIR) {
				acc_dirs++;
				*(path+i) = '/'; strcpy(path+i+1, fn);
				res = scan_files(path);
				*(path+i) = '\0';
				if (res != FR_OK) break;
			} else {
//				xprintf("%s/%s\n", path, fn);
				acc_files++;
				acc_size += Finfo.fsize;
			}
		}
	}

	return res;
}

static void IoInit(void) 
{
	RTCTime  current_time;

	SystemInit(); 

	SysTick_Config(SystemFrequency/1000 - 1); /* Generate interrupt each 1 ms   */

	LPC17xx_RTC_Init ();
	current_time.RTC_Sec = 0;
	current_time.RTC_Min = 0;
	current_time.RTC_Hour = 0;
	current_time.RTC_Mday = 1;
	current_time.RTC_Wday = 0;
	current_time.RTC_Yday = 0;		/* current date 01/01/2010 */
	current_time.RTC_Mon = 1;
	current_time.RTC_Year = 2010;
	LPC17xx_RTC_SetTime( &current_time );		/* Set local time */
	LPC17xx_RTC_Start ();

	LPC17xx_UART_Init(115200);

	LPC_GPIO1 -> FIODIR |= (1U<<28) | (1U<<29) | (1U<<31);		/* P1.16..23 defined as Outputs */		
}


int main ()
{
	char *ptr, *ptr2;
	long p1, p2, p3;
	FRESULT f_res;
	DRESULT d_res;
	BYTE b1;
	WORD w1;
	UINT s1, s2, cnt; 
	DWORD ofs = 0, sect = 0;
	FATFS *fs;				/* Pointer to file system object */
	RTCTime rtc;

	IoInit(); 

	//xputs("\nFatFs module test monitor for LPC17xx " VERSION_STRING "\n");
    xputs("\nFatFs module test monitor for LPC17xx (" __DATE__  __TIME__ ")\n");

	for (;;) {
		xputc('>');
		ptr = linebuf;
		get_line(ptr, sizeof(linebuf));

		switch (*ptr++) {

		case 'm' :
			switch (*ptr++) {
			case 'd' :	/* md <address> [<count>] - Dump memory */
				if (!xatoi(&ptr, &p1)) break;
				if (!xatoi(&ptr, &p2)) p2 = 128;
				for (ptr=(char*)p1; p2 >= 16; ptr += 16, p2 -= 16)
					put_dump((BYTE*)ptr, (UINT)ptr, 16);
				if (p2) put_dump((BYTE*)ptr, (UINT)ptr, p2);
				break;
			}
			break;
		case 'd' :
			switch (*ptr++) {
			case 'd' :	/* dd [<lba>] - Dump sector */
				if (!xatoi(&ptr, &p2)) p2 = sect;
				d_res = disk_read(0, Buff, p2, 1);
				if (d_res) { xprintf("rc=%d\n", (WORD)d_res); break; }
				sect = p2 + 1;
				xprintf("Sector:%lu\n", p2);
				for (ptr=(char*)Buff, ofs = 0; ofs < 0x200; ptr+=16, ofs+=16)
					put_dump((BYTE*)ptr, ofs, 16);			
				break;
			case 'i' :	/* di - Initialize disk */
				xprintf("rc=%d\n", (WORD)disk_initialize(0));	
				break;
			case 's' :	/* ds - Show disk status */
				if (disk_ioctl(0, GET_SECTOR_COUNT, &p2) == RES_OK)
					{ xprintf("Drive size: %lu sectors\n", p2); }
				if (disk_ioctl(0, GET_SECTOR_SIZE, &w1) == RES_OK)
					{ xprintf("Sector size: %u\n", w1); }
				if (disk_ioctl(0, GET_BLOCK_SIZE, &p2) == RES_OK)
					{ xprintf("Erase block size: %lu sectors\n", p2); }
				if (disk_ioctl(0, MMC_GET_TYPE, &b1) == RES_OK)
					{ xprintf("MMC/SDC type: %u\n", b1); }			
				if (disk_ioctl(0, MMC_GET_CSD, Buff) == RES_OK)
					{ xputs("CSD:\n"); put_dump(Buff, 0, 16); }			
				if (disk_ioctl(0, MMC_GET_CID, Buff) == RES_OK)
					{ xputs("CID:\n"); put_dump(Buff, 0, 16); }
				if (disk_ioctl(0, MMC_GET_OCR, Buff) == RES_OK)
					{ xputs("OCR:\n"); put_dump(Buff, 0, 4); }
				if (disk_ioctl(0, MMC_GET_SDSTAT, Buff) == RES_OK) {
					xputs("SD Status:\n");
					for (s1 = 0; s1 < 64; s1 += 16) put_dump(Buff+s1, s1, 16);
				}
				break;
			}
			break;

		case 'b' :
			switch (*ptr++) {
			case 'd' :	/* bd <addr> - Dump R/W buffer */
				if (!xatoi(&ptr, &p1)) break;
				for (ptr=(char*)&Buff[p1], ofs = p1, cnt = 32; cnt; cnt--, ptr+=16, ofs+=16)
					put_dump((BYTE*)ptr, ofs, 16);
				break;

			case 'e' :	/* be <addr> [<data>] ... - Edit R/W buffer */
				if (!xatoi(&ptr, &p1)) break;
				if (xatoi(&ptr, &p2)) {
					do {
						Buff[p1++] = (BYTE)p2;
					} while (xatoi(&ptr, &p2));
					break;
				}
				for (;;) {
					xprintf("%04X %02X-", (WORD)(p1), (WORD)Buff[p1]);
					get_line(linebuf, sizeof(linebuf));
					ptr = linebuf;
					if (*ptr == '.') break;
					if (*ptr < ' ') { p1++; continue; }
					if (xatoi(&ptr, &p2))
						Buff[p1++] = (BYTE)p2;
					else
						xputs("???\n");
				}
				break;

			case 'r' :	/* br <lba> [<num>] - Read disk into R/W buffer */
				if (!xatoi(&ptr, &p2)) break;
				if (!xatoi(&ptr, &p3)) p3 = 1;
				xprintf("rc=%u\n", (WORD)disk_read(0, Buff, p2, p3));
				break;

			case 'w' :	/* bw <lba> [<num>] - Write R/W buffer into disk */
				if (!xatoi(&ptr, &p2)) break;
				if (!xatoi(&ptr, &p3)) p3 = 1;
				xprintf("rc=%u\n", (WORD)disk_write(0, Buff, p2, p3));
				break;

			case 'f' :	/* bf <val> - Fill working buffer */
				if (!xatoi(&ptr, &p1)) break;
				memset(Buff, (BYTE)p1, sizeof(Buff));
				break;

			}
			break;

		case 'f' :
			switch (*ptr++) {

			case 'i' :	/* fi - Force initialized the logical drive */
				put_rc(f_mount(0, &Fatfs[0]));
				break;

			case 's' :	/* fs - Show logical drive status */
				f_res = f_getfree("", (DWORD*)&p2, &fs);
				if (f_res) { put_rc(f_res); break; }
				xprintf("FAT type = %u\nBytes/Cluster = %lu\nNumber of FATs = %u\n"
						"Root DIR entries = %u\nSectors/FAT = %lu\nNumber of clusters = %lu\n"
						"FAT start (lba) = %lu\nDIR start (lba,clustor) = %lu\nData start (lba) = %lu\n\n",
						(WORD)fs->fs_type, (DWORD)fs->csize * 512, (WORD)fs->n_fats,
						fs->n_rootdir, fs->sects_fat, (DWORD)fs->max_clust - 2,
						fs->fatbase, fs->dirbase, fs->database
				);
				acc_size = acc_files = acc_dirs = 0;
#if _USE_LFN
				Finfo.lfname = Lfname;
				Finfo.lfsize = sizeof(Lfname);
#endif
				f_res = scan_files(ptr);
				if (f_res) { put_rc(f_res); break; }
				xprintf("%u files, %lu bytes.\n%u folders.\n"
						"%lu KB total disk space.\n%lu KB available.\n",
						acc_files, acc_size, acc_dirs,
						(fs->max_clust - 2) * (fs->csize / 2), p2 * (fs->csize / 2)
				);
				break;

			case 'l' :	/* fl [<path>] - Directory listing */
				while (*ptr == ' ') ptr++;
				f_res = f_opendir(&Dir, ptr);
				if (f_res) { put_rc(f_res); break; }
				p1 = s1 = s2 = 0;
				for(;;) {
#if _USE_LFN
					Finfo.lfname = Lfname;
					Finfo.lfsize = sizeof(Lfname);
#endif
					f_res = f_readdir(&Dir, &Finfo);
					if ((f_res != FR_OK) || !Finfo.fname[0]) break;
					if (Finfo.fattrib & AM_DIR) {
						s2++;
					} else {
						s1++; p1 += Finfo.fsize;
					}
					xprintf("%c%c%c%c%c %u/%02u/%02u %02u:%02u %9lu  %s",
							(Finfo.fattrib & AM_DIR) ? 'D' : '-',
							(Finfo.fattrib & AM_RDO) ? 'R' : '-',
							(Finfo.fattrib & AM_HID) ? 'H' : '-',
							(Finfo.fattrib & AM_SYS) ? 'S' : '-',
							(Finfo.fattrib & AM_ARC) ? 'A' : '-',
							(Finfo.fdate >> 9) + 1980, (Finfo.fdate >> 5) & 15, Finfo.fdate & 31,
							(Finfo.ftime >> 11), (Finfo.ftime >> 5) & 63,
							Finfo.fsize, &(Finfo.fname[0]));
#if _USE_LFN
					xprintf("  %s\n", Lfname);
#else
					xputc('\n');
#endif
				}
				xprintf("%4u File(s),%10lu bytes total\n%4u Dir(s)", s1, p1, s2);
				if (f_getfree(ptr, (DWORD*)&p1, &fs) == FR_OK)
					xprintf(", %10lu bytes free\n", p1 * fs->csize * 512);
				break;

			case 'o' :	/* fo <mode> <file> - Open a file */
				if (!xatoi(&ptr, &p1)) break;
				while (*ptr == ' ') ptr++;
				put_rc(f_open(&File1, ptr, (BYTE)p1));
				break;

			case 'c' :	/* fc - Close a file */
				put_rc(f_close(&File1));
				break;

			case 'e' :	/* fe - Seek file pointer */
				if (!xatoi(&ptr, &p1)) break;
				f_res = f_lseek(&File1, p1);
				put_rc(f_res);
				if (f_res == FR_OK)
					xprintf("fptr=%lu(0x%lX)\n", File1.fptr, File1.fptr);
				break;

			case 'd' :	/* fd <len> - read and dump file from current fp */
				if (!xatoi(&ptr, &p1)) break;
				ofs = File1.fptr;
				while (p1) {
					if ((UINT)p1 >= 16) { cnt = 16; p1 -= 16; }
					else 				{ cnt = p1; p1 = 0; }
					f_res = f_read(&File1, Buff, cnt, &cnt);
					if (f_res != FR_OK) { put_rc(f_res); break; }
					if (!cnt) break;
					put_dump(Buff, ofs, cnt);
					ofs += 16;
				}
				break;

			case 'r' :	/* fr <len> - read file */
				if (!xatoi(&ptr, &p1)) break;
				p2 = 0;
				Timer = 0;
				while (p1) {
					if ((UINT)p1 >= blen) {
						cnt = blen; p1 -= blen;
					} else {
						cnt = p1; p1 = 0;
					}
					f_res = f_read(&File1, Buff, cnt, &s2);
					if (f_res != FR_OK) { put_rc(f_res); break; }
					p2 += s2;
					if (cnt != s2) break;
				}
				xprintf("%lu bytes read with %lu kB/sec.\n", p2, p2 / Timer);
				break;

			case 'w' :	/* fw <len> <val> - write file */
				if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2)) break;
				memset(Buff, (BYTE)p2, blen);
				p2 = 0;
				Timer = 0;
				while (p1) {
					if ((UINT)p1 >= blen) {
						cnt = blen; p1 -= blen;
					} else {
						cnt = p1; p1 = 0;
					}
					f_res = f_write(&File1, Buff, cnt, &s2);
					if (f_res != FR_OK) { put_rc(f_res); break; }
					p2 += s2;
					if (cnt != s2) break;
				}
				xprintf("%lu bytes written with %lu kB/sec.\n", p2, p2 / Timer);
				break;

			case 'n' :	/* fn <old_name> <new_name> - Change file/dir name */
				while (*ptr == ' ') ptr++;
				ptr2 = strchr(ptr, ' ');
				if (!ptr2) break;
				*ptr2++ = 0;
				while (*ptr2 == ' ') ptr2++;
				put_rc(f_rename(ptr, ptr2));
				break;

			case 'u' :	/* fu <name> - Unlink a file or dir */
				while (*ptr == ' ') ptr++;
				put_rc(f_unlink(ptr));
				break;

			case 'v' :	/* fv - Truncate file */
				put_rc(f_truncate(&File1));
				break;

			case 'k' :	/* fk <name> - Create a directory */
				while (*ptr == ' ') ptr++;
				put_rc(f_mkdir(ptr));
				break;

			case 'a' :	/* fa <atrr> <mask> <name> - Change file/dir attribute */
				if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2)) break;
				while (*ptr == ' ') ptr++;
				put_rc(f_chmod(ptr, p1, p2));
				break;

			case 't' :	/* ft <year> <month> <day> <hour> <min> <sec> <name> - Change timestamp */
				if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2) || !xatoi(&ptr, &p3)) break;
				Finfo.fdate = ((p1 - 1980) << 9) | ((p2 & 15) << 5) | (p3 & 31);
				if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2) || !xatoi(&ptr, &p3)) break;
				Finfo.ftime = ((p1 & 31) << 11) | ((p1 & 63) << 5) | ((p1 >> 1) & 31);
				put_rc(f_utime(ptr, &Finfo));
				break;

			case 'x' : /* fx <src_name> <dst_name> - Copy file */
				while (*ptr == ' ') ptr++;
				ptr2 = strchr(ptr, ' ');
				if (!ptr2) break;
				*ptr2++ = 0;
				while (*ptr2 == ' ') ptr2++;
				xprintf("Opening \"%s\"", ptr);
				f_res = f_open(&File1, ptr, FA_OPEN_EXISTING | FA_READ);
				xputc('\n');
				if (f_res) {
					put_rc(f_res);
					break;
				}
				xprintf("Creating \"%s\"", ptr2);
				f_res = f_open(&File2, ptr2, FA_CREATE_ALWAYS | FA_WRITE);
				xputc('\n');
				if (f_res) {
					put_rc(f_res);
					f_close(&File1);
					break;
				}
				xprintf("Copying file...");
				Timer = 0;
				p1 = 0;
				for (;;) {
					f_res = f_read(&File1, Buff, blen, &s1);
					if (f_res || s1 == 0) break;   /* error or eof */
					f_res = f_write(&File2, Buff, s1, &s2);
					p1 += s2;
					if (f_res || s2 < s1) break;   /* error or disk full */
				}
				xprintf("%lu bytes copied with %lu kB/sec.\n", p1, p1 / Timer);
				f_close(&File1);
				f_close(&File2);
				break;
#if _FS_RPATH
			case 'g' :	/* fg <path> - Change current directory */
				while (*ptr == ' ') ptr++;
				put_rc(f_chdir(ptr));
				break;

			case 'j' :	/* fj <drive#> - Change current drive */
				if (xatoi(&ptr, &p1)) {
					put_rc(f_chdrive((BYTE)p1));
				}
				break;
#endif
#if _USE_MKFS
			case 'm' :	/* fm <partition rule> <cluster size> - Create file system */
				if (!xatoi(&ptr, &p2) || !xatoi(&ptr, &p3)) break;
				xprintf("The drive 0 will be formatted. Are you sure? (Y/n)=");
				get_line(ptr, sizeof(linebuf));
				if (*ptr == 'Y')
					put_rc(f_mkfs(0, (BYTE)p2, (WORD)p3));
				break;
#endif
			case 'z' :	/* fz [<rw size>] - Change R/W length for fr/fw/fx command */
				if (xatoi(&ptr, &p1) && p1 >= 1 && (size_t)p1 <= sizeof(Buff))
					blen = p1;
				xprintf("blen=%u\n", blen);
				break;
			}
			break;

			case 't' :	/* t [<year> <mon> <mday> <hour> <min> <sec>] */
				if (xatoi(&ptr, &p1)) {
					rtc.RTC_Year = (WORD)p1;
					xatoi(&ptr, &p1); rtc.RTC_Mon = (BYTE)p1;
					xatoi(&ptr, &p1); rtc.RTC_Mday = (BYTE)p1;
					xatoi(&ptr, &p1); rtc.RTC_Hour = (BYTE)p1;
					xatoi(&ptr, &p1); rtc.RTC_Min = (BYTE)p1;
					if (!xatoi(&ptr, &p1)) break;
					rtc.RTC_Sec = (BYTE)p1;
					rtc_settime(&rtc);
				}
				rtc_gettime(&rtc);
				xprintf("%u/%u/%u %02u:%02u:%02u\n", rtc.RTC_Year, rtc.RTC_Mon, rtc.RTC_Mday, rtc.RTC_Hour, rtc.RTC_Min, rtc.RTC_Sec);
				break;								
		}
	}											  
	
}




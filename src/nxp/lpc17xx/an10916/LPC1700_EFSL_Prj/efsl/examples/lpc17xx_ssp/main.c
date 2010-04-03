/******************************************************************************
 
 efsl Demo-Application for NXP LPC1768 Cortex-M3
 
 Copyright (c) 2009

 
 *****************************************************************************/
# include <stdio.h>
# include <string.h>
# include "efs.h"
# include "ls.h"
#include "Core_CM3/lpc17xx.h"
#include "Utility/monitor.h"

static char LogFileName[] = 
 "efsltst1.txt"; 				// OK
// "/efsltst1.txt"; 				// OK
//"/efsldir1/efsltst9.txt"; 				// OK
// "efsltstlongfilename.txt";	// do not support LFN

EmbeddedFile filer, filew;
uint16_t e;
uint8_t buf[513];

EmbeddedFileSystem  efs;
EmbeddedFile        file;
DirList             list;
uint8_t       file_name[13];
uint32_t        size;

int main()
{
	int8_t res;

	SystemInit();
	LPC17xx_UART_Init(115200);

	xprintf("\nMMC/SD Card Filesystem Test (P:LPC1768 L:EFSL)\n");

	xprintf("CARD init...");

	// init file system
	if ( ( res = efs_init( &efs, 0 ) ) != 0 ) {
		xprintf("failed with %i\n",res);
	}
	else 
	{
		xprintf("ok\n");
		xprintf("Directory of 'root':\n");
		
		// list files in root directory
		ls_openDir( &list, &(efs.myFs) , "/");
		while ( ls_getNext( &list ) == 0 ) {
			// list.currentEntry is the current file
			list.currentEntry.FileName[LIST_MAXLENFILENAME-1] = '\0';
			xprintf("%s, 0x%x bytes\n", list.currentEntry.FileName, list.currentEntry.FileSize ) ;
		}

		// read file
		if ( file_fopen( &filer, &efs.myFs , LogFileName , 'r' ) == 0 ) {
			xprintf("\nFile %s open. Content:\n", LogFileName);
			while ( ( e = file_read( &filer, 512, buf ) ) != 0 ) {
				buf[e]='\0';
				xprintf("%s\n", (char*)buf);
			}
			xprintf("\n");
			file_fclose( &filer );
		}
		else
			xprintf("File %s open failed.\n", LogFileName);	

		// write file
		if ( file_fopen( &filew, &efs.myFs , LogFileName , 'a' ) == 0 ) {
			xprintf("File %s open for append. Appending...", LogFileName);
			strcpy((char*)buf, "Appending this line on " __TIME__ " "__DATE__ "\r\n");
			if ( file_write( &filew, strlen((char*)buf), buf ) == strlen((char*)buf) ) {
				xprintf("ok\n");
			}
			else {
				xprintf("fail\n");
			}
			file_fclose( &filew );
		}
		else
			xprintf("File %s open failed.\n", LogFileName);

		// read file
		if ( file_fopen( &filer, &efs.myFs , LogFileName , 'r' ) == 0 ) {
			xprintf("\nFile %s open. Content:\n", LogFileName);
			while ( ( e = file_read( &filer, 512, buf ) ) != 0 ) {
				buf[e]='\0';
				xprintf("%s\n", (char*)buf);
			}
			xprintf("\n");
			file_fclose( &filer );
		}
		else
			xprintf("File %s open failed.\n", LogFileName);

		// close file system
		fs_umount( &efs.myFs ) ;
		xprintf("EFSL test complete.\n");

	}

	while (1);
}

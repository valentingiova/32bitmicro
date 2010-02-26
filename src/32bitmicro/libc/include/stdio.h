/*
 * 32bitmicro libc stdio
 * $URL$
 * $ID$

Copyright (c) 2010, 32bitmicro
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation 
and/or other materials provided with the distribution.
Neither the name of the 32bitmicro nor the names of its contributors may be used to endorse or promote products derived from this software without 
specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _STDIO_H_
#define _STDIO_H_

#include <stddef.h>
#include <sys/types.h>

#ifdef __STDC__
#include <stdarg.h>
#endif

#ifndef EOF
# define EOF (-1)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define	__SLBF	0x0001		/* line buffered */
#define	__SNBF	0x0002		/* unbuffered */
#define	__SRD	0x0004		/* OK to read */
#define	__SWR	0x0008		/* OK to write */
	/* RD and WR are never simultaneously asserted */
#define	__SRW	0x0010		/* open for reading & writing */
#define	__SEOF	0x0020		/* found EOF */
#define	__SERR	0x0040		/* found error */
#define	__SMBF	0x0080		/* _buf is from malloc */
#define	__SAPP	0x0100		/* fdopen()ed in append mode - so must  write to end */
#define	__SSTR	0x0200		/* this is an sprintf/snprintf string */
#define	__SOPT	0x0400		/* do fseek() optimisation */
#define	__SNPT	0x0800		/* do not do fseek() optimisation */
#define	__SOFF	0x1000		/* set iff _offset is in fact correct */
#define	__SMOD	0x2000		/* true => fgetline modified _p text */

typedef off_t fpos_t;		/* stdio file position type */


typedef	struct FILE_OP_t {
	int	(*_fopen)(void *, const char *, int, int);
	int	(*_fclose)(void *);
	int	(*_fread)(void *, char *, int);
	fpos_t	(*_fseek)(void *, fpos_t, int);
	int	(*_fwrite)(void *, const char *, int);
} FILE_OP;


typedef	struct FILE_t {
	short	_flags;		/* flags, below; this FILE is free if 0 */
	short	_file;		/* fileno, if Unix descriptor, else -1 */
	/* operations */
	FILE_OP* _fileop;
} FILE;

extern FILE __files[];
#define	stdin	(&__files[0])
#define	stdout	(&__files[1])
#define	stderr	(&__files[2])

/* syscalls internal */
extern void __init_files(void);
extern FILE* __get_file(int file);
extern FILE_OP* __get_file_op(int file);


/* stdio internal */
extern int __sflags (char *mode, int *optr);

/* stdio public */
extern int fgetc(FILE *fp);
extern char *fgets(char *buf, int n, FILE *fp);

extern int fputc (int c, FILE *fp);
extern int fputs(const char *s, FILE *fp);

extern int getc (register FILE *fp);
extern int getchar(void);
extern char *gets(char *buf);

extern int putc(int c, register FILE *fp);
extern int putchar(int c);
extern int puts(const char *s);

extern int printf(const char *format, ...);
extern int fprintf(FILE *fp, const char *format, ...);
extern int sprintf(char *out, const char *format, ...);

/* vsnprintf */
#define vsnprintf rpl_vsnprintf
#define snprintf rpl_snprintf
#define vasprintf rpl_vasprintf
#define asprintf rpl_asprintf
/* extern int rpl_vsnprintf(char *str, size_t size, const char *format, va_list args); */
/* extern int rpl_vasprintf(char **ret, const char *format, va_list ap); */
extern int rpl_snprintf(char *str, size_t size, const char *format, ...);

/* streams */
extern FILE* fopen(char *file, char *mode);

#ifdef __cplusplus
}
#endif

#endif

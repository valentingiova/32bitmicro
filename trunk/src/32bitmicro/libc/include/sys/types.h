/*
 * 32bitmicro libc types.h
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

#ifndef _SYS_TYPES_H_
#define	_SYS_TYPES_H_

#include <sys/cdefs.h>
#include <sys/inttypes.h>

/* machine types */
typedef	unsigned char	u_char;
typedef	unsigned short	u_short;
typedef	unsigned int	u_int;
typedef	unsigned long	u_long;

typedef uint8_t		u_int8_t;
typedef uint16_t	u_int16_t;
typedef uint32_t	u_int32_t;
typedef uint64_t	u_int64_t;

typedef	u_int32_t	blkcnt_t;         /* file block counts */
typedef	u_int32_t	blksize_t;        /* block sizes */
typedef	long		clock_t;          /* system time in clock ticks or CLOCKS_PER_SEC in <time.h> */
typedef	u_int32_t	clockid_t;        /* clock ID type for clock, timer functions */
typedef	u_int32_t	dev_t;            /* device IDs */
typedef	u_int32_t	fsblkcnt_t;       /* file system block counts */
typedef	u_int32_t	fsfilcnt_t;       /* file system file counts */
typedef	u_int32_t	gid_t;            /* group IDs */
typedef	u_int32_t	id_t;             /* identifier, must contain: pid_t, uid_t or gid_t */
typedef	u_int32_t	ino_t;            /* file serial no */
typedef	long		key_t;            /* IPC */
typedef	u_int16_t	mode_t;           /* file permissions/attributes */
typedef	u_int16_t	nlink_t;          /* link counts */
typedef	long		off_t;            /* file size */
typedef	u_int32_t	pid_t;            /* process, process group IDs */

#ifndef __SIZE_T_DEFINED
typedef	u_int32_t	size_t;           /* sizes */
#define __SIZE_T_DEFINED
#endif

typedef	u_int32_t	ssize_t;          /* count of bytes or error */
typedef	long		suseconds_t;      /* time in microseconds */
typedef	long		time_t;           /* time in seconds */
typedef	u_int32_t	timer_t;          /* timer ID see timer_create() */
typedef	u_int32_t	uid_t;            /* user IDs */
typedef	long		useconds_t;       /* time in microseconds */


#endif
 
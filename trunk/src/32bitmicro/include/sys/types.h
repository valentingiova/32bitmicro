/*
 * 32bitmicro syscalls.c 32bitmicro newlib syscalls

 * $URL$
 * $ID$

Copyright (c) 2009, 32bitmicro
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

#ifndef __SYS_TYPES_H__
#define __SYS_TYPES_H__

#include <stddef.h>

#if (!defined(_STDDEF_H) && !defined(_STDDEF_H_) && !defined(_ANSI_STDDEF_H) )
#if !defined(_SIZE_T)
#define _SIZE_T
typedef unsigned int size_t;
#endif
#if !defined(_PID_T)
#define _PID_T
typedef int pid_t;
#endif
#endif

typedef unsigned int dev_t;
typedef unsigned int ino_t;
typedef unsigned int mode_t;
typedef unsigned int nlink_t;
typedef unsigned int uid_t;
typedef unsigned int gid_t;
typedef unsigned int off_t;
typedef unsigned int fpos_t;
typedef unsigned int clock_t;
typedef unsigned int time_t;
typedef unsigned int suseconds_t;
typedef	long	daddr_t;
typedef	char*	caddr_t;


#if defined (__GCC__)
#define __long_long long long
#define __ulong_long unsigned long long
typedef long long lldiv_t;
typedef unsigned long long ulldiv_t;
#elif defined (_MSC_VER)
#define __long_long __int64 
#define __ulong_long unsigned __int64 
typedef __int64 lldiv_t;
typedef unsigned __int64 ulldiv_t;
typedef unsigned short WCHAR;
#else
#define __long_long long long
#define __ulong_long unsigned long long
typedef long lldiv_t;
typedef unsigned long ulldiv_t;
#endif

#endif /* __SYS_TYPES_H__ */

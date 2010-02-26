/*
 * 32bitmicro libc cmsis syscalls
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

#include "../../../libc/include/stdio.h"
#include "../../../libc/include/syscalls.h"

#ifdef __GNUC__
#define __WEAK  __attribute__ ((weak))  
#else
#define __WEAK 
#endif

#define MAX_FILE 3


FILE    __files[MAX_FILE];

void __WEAK abort(void)
{
}

void __WEAK _exit(int code)
{
}

int __WEAK _open(const char *name, int flags, int mode)
{
	return -1;
}

int __WEAK _close(int file)
{
	return -1;
}

int __WEAK _read(int file, char *ptr, int len)
{
	return -1;
}

int __WEAK _seek(int file, int offset, int whence)
{
	return -1;
}

int __WEAK _write(int file, char *ptr, int len)
{
	return -1;
}

void* __WEAK _malloc(size_t numbytes)
{
	return NULL;
}

void __WEAK _free(void *ptr)
{
}

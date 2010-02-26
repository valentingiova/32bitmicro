/*
 * 32bitmicro libc stdlib
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


#ifndef _STDLIB_H_
#define _STDLIB_H_

#include <stddef.h>
#include <sys/types.h>


typedef struct
{
	int quot;
	int rem;
} div_t;

typedef struct
{
	long quot;
	long rem;
} ldiv_t;
         
extern long strtol (const char *nptr, char **ptr, int base);

extern int abs(int i);
extern int atoi (const char *s);
extern long atol(const char *s);

extern void *malloc(size_t nbytes);
extern void free(void *aptr);
extern void *calloc(size_t n, size_t size);

extern div_t div (int num, int denom);
extern ldiv_t ldiv (long num, long denom);

#ifndef RAND_MAX
#define RAND_MAX	0x7fffffffL
#endif

extern int rand_r(u_int *seed);
extern int rand(void);
extern void srand(unsigned int seed);

#endif

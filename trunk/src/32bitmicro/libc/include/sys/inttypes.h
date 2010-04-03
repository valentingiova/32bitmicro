/*
 * 32bitmicro libc include inttytpes Makefile
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


#ifndef _INTTYPES_H_
#define _INTTYPES_H_

#ifndef __int8_t_defined
typedef signed char int8_t;
#define __int8_t_defined 1
#endif

#ifndef __uint8_t_defined
typedef unsigned char uint8_t;
#define __uint8_t_defined 1
#endif

#ifndef __int16_t_defined
typedef short  int16_t;
#define __int16_t_defined 1
#endif

#ifndef __uint16_t_defined
typedef unsigned short uint16_t;
#define __uint16_t_defined 1
#endif

#ifndef __int32_t_defined
typedef long int32_t;
#define __int32_t_defined 1
#endif

#ifndef __uint32_t_defined
typedef unsigned long uint32_t;
#define __uint32_t_defined 1
#endif

#ifndef __int64_defined
typedef long long int64_t;
#define __int64_defined 1
#endif

#ifndef __uint64_t_defined
typedef unsigned long long uint64_t;
#define __uint64_t_defined 1
#endif

#ifndef __intptr_t_defined
typedef int intptr_t;
#define __intptr_t_defined 1
#endif

#ifndef __uintptr_t_defined
typedef unsigned int uintptr_t;
#define __uintptr_t_defined 1
#endif

#endif

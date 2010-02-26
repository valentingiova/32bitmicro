/*
 * 32bitmicro libc limits
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

#ifndef _LIMITS_H
#define _LIMITS_H

#define CHAR_BIT 8                      /* number of bits for byte) */
#define SCHAR_MIN -127                  /* minimum value for type signed char */
#define SCHAR_MAX +127                  /* maximum value for type signed char */
#define UCHAR_MAX 255                   /* maximum value for type unsigned char */
#define CHAR_MIN SCHAR_MIN              /* minimum value for type char */
#define CHAR_MAX SCHAR_MAX              /* maximum value for type char */
#define MB_LEN_MAX 1                    /* maximum number of bytes in a multibyte character */
#define SHRT_MIN -32767                 /* minimum value for type short int */
#define SHRT_MAX +32767                 /* maximum value for type short int */
#define USHRT_MAX 65535                 /* maximum value for type unsigned short int */
#define INT_MIN -2147483647             /* minimum value for type int */
#define INT_MAX 2147483647              /* maximum value for type int */
#define UINT_MAX 4294967295             /* maximum value for type unsigned int */
#define LONG_MIN -2147483647            /* minimum value for type long int */
#define LONG_MAX +2147483647            /* maximum value for type long int */
#define ULONG_MAX 4294967295            /* maximum value for type unsigned long int */
#define LLONG_MIN -9223372036854775807  /* minimum value for type long long int */
#define LLONG_MAX +9223372036854775807  /* maximum value for type long long int */
#define ULLONG_MAX 18446744073709551615 /* maximum value for type unsigned long long int */

#endif

#
# * 32bitmicro NXP lpc13xx StackUsage_1343 Makefile
# * $URL$
# * $ID$
#
#Copyright (c) 2010, 32bitmicro
#All rights reserved.
#
#Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
#Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
#Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation 
#and/or other materials provided with the distribution.
#Neither the name of the 32bitmicro nor the names of its contributors may be used to endorse or promote products derived from this software without 
#specific prior written permission.
#
#THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
#BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
#SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
#DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
#OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
#NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

# paths
32BITMICRO= /32bitmicro
NXPROOT=$(32BITMICRO)/src/nxp
LPC13XXROOT=$(NXPROOT)/lpc13xx

# Project configuration
PROJECT=StackUsage_1343
TARGET_MCU=lpc1343


# Target libc
TARGET_LIBC=newlib
#TARGET_LIBC=default

# Sources
CSRC=src/main.c
CSRC+=src/debug.c
CSRC+=src/stack.c


# add local include to CFlags
CFLAGS+=-Isrc


# lib_small_printf sources
# To enable float support uncomment line below
#LIB_FLOAT_PRINTF=1
include $(NXPROOT)/lib_small_printf/Makefile.rules


# Top LPC13xx rules
NO_TIMER16=1
include ../Makefile.rules



#
# * 32bitmicro 32bitblaster Makefile
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


# Target configuration
TARGET_MCU?=lpc2148
TARGET_CLOCK?=12000000
TARGET_OS?=standalone

# Project configuration
PROJECT?=jtagblaster
PROJECT_TYPE?=APP
all: $(PROJECT)


# Target SDK configuration
TARGET_SDK?=cs-arm-2009q1
#TARGET_SDK?=cs-arm-2009q3
#TARGET_SDK=sdk-4.3.2-armv7m

# Target libc
TARGET_LIBC=default
#TARGET_LIBC=nolibc


# Target startup file
TARGET_STARTUP=./startup.o

# Additional Libraries

# Host configuration
HOST_OS?=win32
#HOST_OS=linux-x86

# Target output options
TARGET_GEN_BIN=1
TARGET_GEN_MAP=1
TARGET_GEN_CREF=1
TARGET_GEN_LST=1
TARGET_GEN_SYM=1
TARGET_GEN_HEX=1


# Top rules
include ./Makefile.rules

# 32bitmicro configuration and rules
32BITMICRO= /32bitmicro
include $(32BITMICRO)/src/make/Makefile.rules

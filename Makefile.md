# Introduction #

Project Makefile


# Details #


Example
```
# Target configuration
TARGET_MCU=lpc1766
TARGET_CLOCK=12000000
TARGET_OS=standalone


# Project configuration
PROJECT=DEMO
PROJECT_TYPE=APP
all: $(PROJECT)

# Target SDK configuration
TARGET_SDK=cs-arm-2009q1

# Target libc
TARGET_LIBC=default

# Target startup file
#TARGET_STARTUP=

# Additional Libraries
#ADD_CMSIS=CMSIS_V1P20

# Host configuration
HOST_OS=win32

# Sources
ASRC=startup.S
CSRC=main.c

# Flags
CFLAGS=-I.
LDFLAGS=

# 32bitmicro configuration and rules
32BITMICRO=/32bitmicro
include $(32BITMICRO)/src/make/Makefile.rules
```
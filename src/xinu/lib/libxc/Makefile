#
#  Make the Xinu version of the C run-time support library
#
include ../../Makefile.rules.target

ARCH:=${TARGET_PLATFORM}
#ARCH=${TARGET_ARCH}

DIR	=	/32bitmicro/xinu
CFLAGS	=	-g -c -I../../h --freestanding -nostdinc

ifeq ($(ARCH), x86)
CFLAGS+=-ffreestanding -m32 -fomit-frame-pointer -DI386 -D__COM32__
endif

ifeq ($(ARCH), x86)
CFLAGS+=-D__COM32__
endif

SFLAGS	=	-I../../h
AR	=	/bin/ar
LIB	=	${DIR}/lib


arch/${ARCH}/%.o : arch/${ARCH}/%.s
		$(AS) -o $@ $(AFLAGS) $<

.c.o :
		$(CC) $(CFLAGS) $<

# AFILES is plaform dependant

# M68K
ifeq ($(TARGET_ARCH),M68K)
AFILES  =       aldiv.s almul.s alrem.s auldiv.s aulmul.s aulrem.s	\
		blkcopy.s blt.s clear.s float.s ldiv.s lmul.s lrem.s	\
		mcount.s setjmp.s uldiv.s ulmul.s ulrem.s
endif

#i386
ifeq ($(TARGET_ARCH),i386)
AFILES	=	blkcopy.s
endif

ifeq ($(TARGET_ARCH),ARMv7M)
AFILES	=	
endif


AOFILES =	$(patsubst %.s,arch/${ARCH}/%.o,$(AFILES))


CFILES	=	abs.c atof.c atoi.c atol.c bzero.c ctype_.c		\
		doprnt.c memcmp.c memset.c	\
		doscan.c ecvt.c fgets.c fprintf.c fputs.c gets.c	\
		index.c printf.c puts.c qsort.c rand.c rindex.c scanf.c	\
		sprintf.c strcat.c strcmp.c strcpy.c strlen.c strncat.c	\
		strncmp.c strncpy.c swab.c

OFILES	=	abs.o atof.o atoi.o atol.o bzero.o ctype_.o		\
		doprnt.o memcmp.o memset.o	\
		doscan.o ecvt.o fgets.o fprintf.o fputs.o gets.o	\
		index.o printf.o puts.o qsort.o rand.o rindex.o scanf.o	\
		sprintf.o strcat.o strcmp.o strcpy.o strlen.o strncat.o	\
		strncmp.o strncpy.o swab.o ${AOFILES}

all:		libxc.a

libxc.a:	${OFILES}
		rm -f libxc.a
		ar cr libxc.a $(OFILES)
		ranlib libxc.a

install:	libxc.a
		cp libxc.a $(LIB)/libxc.a
		ranlib $(LIB)/libxc.a
		
clean:
		rm -f ${OFILES}

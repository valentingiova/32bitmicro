#
# Make the Xinu configuration program
#

include ../Makefile.rules.host

#LEX    = lex
LEX    = flex
#YACC   = yacc
YACC   = bison -y
CC     = gcc 
#CC     = cc 

DEFS=
CFLAGS = -g ${DEFS}
#LDFLAGS=-l
LDFLAGS=-lfl

CONFIG=config${EXE}

all:		${CONFIG}

${CONFIG}:	lex.yy.c y.tab.c
		${CC} ${CFLAGS} -o ${CONFIG} y.tab.c ${LDFLAGS}

lex.yy.c:	config.l
		$(LEX) config.l

y.tab.c:	config.y
		$(YACC) config.y

install:	config
		${CP} ${CONFIG} ../sys/${CONFIG}

clean: 
		${RM} -f lex.yy.c y.tab.c core ${CONFIG}

#include config.mk

CC = cc
LIBS = #-L${X11LIB} -lX11 ${XINERAMALIBS} ${FREETYPELIBS}

CPPFLAGS = -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_POSIX_C_SOURCE=200809L -DVERSION=\"${VERSION}\" ${XINERAMAFLAGS}
#CFLAGS   = -g -std=c99 -pedantic -Wall -O0 ${INCS} ${CPPFLAGS}
CFLAGS   = -std=c99 -pedantic -Wall -Wno-deprecated-declarations -Os ${INCS} ${CPPFLAGS}
LDFLAGS  = ${LIBS}


SRC = Main.c
OBJ = ${SRC:.c=.o}

all: cliffyc

%.o: %.c
	${CC} -c ${CFLAGS} $<

${OBJ}: # config.h config.mk

#config.h:
#	cp config.def.h $@

cliffyc: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f dwm ${OBJ}

.PHONY: all clean

CC=gcc
PROG=weather
INCS=
SRC=${PROG}.c
PRE=${SRC:.c=.i}
ASM=${PRE:.i=.s}
OBJ=${ASM:.s=.o}
LIBS=gtk+-2.0
CFLAGS=`pkg-config --cflags ${LIBS}` -O2 -Wall
LDFLAGS=`pkg-config --libs ${LIBS}` -O2 -Wall -lcurl

all:
	$(CC) ${CFLAGS} -E ${SRC} -o ${PRE}
	$(CC) -S ${PRE} -o ${ASM}
	$(CC) ${CFLAGS} -c ${ASM} -o ${OBJ}
	$(CC) ${LDFLAGS} ${OBJ} -o ${PROG} 
debug:
	$(CC) ${CFLAGS} -E ${SRC} -o ${PRE} -g
	$(CC) -S ${PRE} -o ${ASM} -g
	$(CC) ${CFLAGS} -c ${ASM} -o ${OBJ} -g
	$(CC) ${LDFLAGS} ${OBJ} -o ${PROG} -g
clean:
	rm -f ${PROG} ${PRE} ${ASM} ${OBJ}
install:
	mkdir -p ${HOME}/bin
	install -m 755 ${PROG} ${HOME}/bin
uninstall:
	rm -f ${HOME}/bin/${PROG}
	rmdir ${HOME}/bin

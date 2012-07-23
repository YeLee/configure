CC=gcc
PROG=weather
INCS=
SRC=${PROG}.c
OBJ=${SRC:.c=.o}
LIBS=gtk+-2.0
FLAGS=`pkg-config --cflags --libs ${LIBS}` -O2 -Wall
all:
	$(CC) ${SRC} ${FLAGS} -o ${PROG} 
clean:
	rm -f ${PROG}

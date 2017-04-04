CC = g++

CFLAGS = -Wall

all: main readin

main: main.o
	${CC} ${CFLAGS} main.o -o main

readin: readin.o
	${CC} ${CFLAGS} readin.o -o readin
	
timing: timing.o
        ${CC} ${CFLAGS} timing.o -o timing

clean: 
	rm -rf *.o

cleanall:
	rm -rf main readin *.o log

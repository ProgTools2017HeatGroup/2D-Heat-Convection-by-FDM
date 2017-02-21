CC = g++

CFLAGS = -Wall

all: readin

readin: readin.o
	${CC} ${CFLAGS} readin.o -o readin

clean: 
	rm -rf *.o

cleanall:
	rm -rf readin *.o

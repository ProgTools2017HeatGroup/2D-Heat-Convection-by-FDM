CC = g++

CPPFLAGS = -Wall

all: main

file_io.o: file_io.cpp
	${CC} ${CPPFLAGS} -c file_io.cpp
    
main.o: main.cpp
	${CC} ${CPPFLAGS} -c main.cpp

main: main.o file_io.o
	${CC} ${CPPFLAGS} main.o file_io.o -o main


clean: 
	rm -rf *.o

cleanall:
	rm -rf main *.o 

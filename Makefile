CC = g++

CPPFLAGS = -Wall

all: main

file_io.o: file_io.cpp
	${CC} ${CPPFLAGS} -c file_io.cpp

utility.o: utility.cpp
	${CC} ${CPPGLAGS} -c utility.cpp

main.o: main.cpp
	${CC} ${CPPFLAGS} -c main.cpp

main: main.o file_io.o utility.o
	${CC} ${CPPFLAGS} main.o file_io.o utility.o -o main

clean: 
	rm -rf *.o

cleanall:
	rm -rf main *.o latex/ html/ 

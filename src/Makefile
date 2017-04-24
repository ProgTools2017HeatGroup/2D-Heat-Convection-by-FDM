CC = g++

CPPFLAGS = -Wall

GSLFLAGS = -I/home/asaxena/Downloads/softwares/gsl/include

LDFLAGS = -L/home/asaxena/Downloads/softwares/gsl/lib -lm -lgsl -lgslcblas

EXEC = ../fdm2D

.c.o:
	${CC} ${CPPFLAGS} $<

$(EXEC): main.o file_io.o utility.o generate_regular_grid.o boundary.o stability_condition.o calculate_temperature.o calculate_velocity.o generate_output_in_vts.o
	${CC} ${CPPFLAGS} $^ -o $@  ${GSLFLAGS} ${LDFLAGS}

clean: 
	rm -rf *.o

cleanall:
	rm -rf *.o $(EXEC) ../latex/ ../html/ 

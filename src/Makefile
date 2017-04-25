CC = g++

CPPFLAGS = -Wall

GSLFLAGS = -I/public/apps/gsl/1.16/gcc.4.4.7/include/gsl

LDFLAGS = -L/public/apps/gsl/1.16/gcc.4.4.7/lib -lm -lgsl -lgslcblas

EXEC = ../fdm2D

.c.o:
	${CC} ${CPPFLAGS} $<

$(EXEC): main.o file_io.o utility.o generate_regular_grid.o initial_temp.o set_density.o generate_output_in_vts.o stability_condition.o calculate_temperature.o calculate_velocity.o generate_output_in_vts.o
	${CC} ${CPPFLAGS} $^ -o $@  ${GSLFLAGS} ${LDFLAGS}

clean: 
	rm -rf *.o 

cleanall:
	rm -rf *.o $(EXEC) 

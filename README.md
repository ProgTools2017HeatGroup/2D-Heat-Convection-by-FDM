# 2D-Heat-Convection-by-FDM


This code is for solving heat convection in a 2D rectangular box using finite difference method.

To build form the source code:
1. Download the source package
2. install GSL libarary, for example, in Ubuntu, you can use sudo apt-get install libgs10-dev libgsl0ldbl to install it
3. Before "make", you should go to the ./src subdirectory and edit "Makefile" to change the gsl library location to where you installed it
   for example, change GSLFLAGS = -I/usr/include/gsl to -I/...your path.../gsl/include; change LDFLAGS = -L/usr/lib to -L/...your path.../gsl/lib     
4. Under the parent directory, run "make" to build the code

Runing code
1. Take reference from the parameter.in file to generate your own input file with desired value
2. Under the same directory, run "./fdm2D -i parameters.in -o log"
3. Check the value of parameter.in file follow the error message on screen if error occur
4. Output file is in ".vts" files, in which the velocity and tempreture information is stored
5. Output frequency is calculated to be stable based on input value

Units

Our code itself has no internal knowledge of units. which means the user has the freedom to choose a preferred units system, as long as they are consistent. Also, the user may have to scale the units to make the solver stable.

Domain dimensions

The domain in this model is currently 100*100, users can modify it in the parameter.in file. 

Total time steps

The user can modify total time step to model to iterate, the default value in the parameter.in file is 200

Result visualization

The output result is in file type .vts for each time step
To view the output files, using ParaView or any other software you desire

# 2D-Heat-Convection-by-FDM


This code is for solving heat convection in a 2D rectangular box using finite difference method.

To build form the source code:
1. Download the source package
2. Under the dirctory of source package, run "make" to build the code

Runing code
1. Take reference from the parameter.in file to generate your own input file with desired value
2. Under the same directory, run "./main -i parameters.in -o log"
3. Check the value of parameter.in file follow the error message on screen if error occur
4. Output file is in ".vts" files, in which the velocity and tempreture information is stored
5. Output frequency is calculated to be stable based on input value
6. To view the output file, using ParaView or any other software you desire


For more information about the algorithm behind, please check our wiki page.

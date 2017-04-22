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

Units
Our code itself has no internal knowledge of units. which means the user has the freedom to choose a preferred units system, as long as they are consistent. Also, the user may have to scale the units to make the solver stable.

Domain dimensions
The domain in this model is currently 100*100, users can modify it in the parameter.in file. 

Total time steps
The user can modify total time step to model to iterate, the default value in the parameter.in file is 200

Result visualization
The output result is in file type .vts for each time step
To view the output files, using ParaView or any other software you desire

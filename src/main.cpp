/**
 * @mainpage 2D Heat Convection Simulation Program
 *
 * This is the documentation for 2D Heat Convection Simulation Package.
 * It contains all the relevant info.
 */
#include <iostream>
#include <fstream>
#include <time.h>
#include <unistd.h> 
#include <cstring>
#include <vector>

#include "generate_regular_grid.h"
#include "initial_temp.h"
#include "file_io.h"
#include "utility.h"
#include "structs.h"
#include "set_density.h"
#include "calculate_temperature.h"
#include "calculate_velocity.h"
#include "stability_condition.h"
#include "generate_output_in_vts.h"

using namespace std;
/**
 * @short Main program
 * @file  main.cpp
 * @author Arushi Saxena, Hao Lu, Jia Zhang
 * @return 0 on success
 *
 * This program solves for the 2-D fluid convection in a Box due to an initial temperature perturbation 
 * using finite difference method over a regular grid. For simplicity, the fluid is assumed is assumed 
 * incompressible, Newtonian and slowly convecting. Our code itself has no internal knowledge of units. 
 * The purpose of this program is to simulate the fluid convection under different initial conditions, 
 * boundary conditions and initial temperature perturbations.
 */

int main(int argc, char* argv[]) {
    
    //simple timing function
    clock_t t1 = clock();  

    char *infile, *logfile;

    check_argu(argc, argv, &infile, &logfile);

    Parameters params;
    vector<string> str;

    read_infile(infile, str);

    cout << "Storing input value" << endl;

    //Store input parameter value
    store_params(str, &params);

    cout << "generating input logfile" << endl;

    //Write input value to logfile
    write_logfile(logfile, &params);

    // get points in X and Y direction for printing in output
    int** X = generate_x_points (xe, ye, nx, ny);
    int** Y = generate_y_points (xe, ye, nx, ny);
     get grid spacing to be used in later programs
    double dy = ye/(ny-1);
    double dx = xe/(nx-1);
    
    // allocate memory for initial temperature
    gsl_matrix* To = gsl_matrix_alloc(ny,nx);

    set_back_value (To, ny, nx, Temp);


    if (pert_type == "BOX") {
        set_box (To, dx, dy, length, width, xo, yo, pert_T, xe, ye);
        
    } else if (pert_type == "DISK") {
        set_disk (To, dx, dy, radius, xo, yo, pert_T, xe, ye);
    }
    
    else if (pert_type == "GAUSSIAN") {
        set_gaussian (To, dx, dy, sigma, xo, yo, pert_T, xe, ye);
    }

    // allocate memory for modified density
    gsl_matrix* rho_m = gsl_matrix_alloc(ny,nx);
    set_density (To, rho_m, pert_T, expa, rho, nx, ny);
 

    // allocate memory for velocities
    gsl_matrix* vx = gsl_matrix_alloc(ny,nx);
    gsl_matrix* vy = gsl_matrix_alloc(ny,nx);
    
    cout << "Generating velocity field" << endl;
    
    // Calculate horizontal velocity for each mesh grid in the domain based on input and boundary condition
    set_horizontal_velocity (rho_m, nx, ny, vis, dx, dy, left_con, right_con, top_con, bottom_con, velo_left, 
            velo_right,  velo_top,  velo_bottom, vx);
    set_vertical_velocity (rho_m, nx, ny, vis, dx, dy, left_con, right_con, top_con, bottom_con, velo_left, 
            velo_right,  velo_top,  velo_bottom, vy);
    
    //Calculates stable iteration time step based on the user input
    
    cout << "Calculating stable iteration time step based input" << endl;
    
    double dt = stable_time (diff, vx, vy, dx, dy);
    cout << dt << endl;

    // allocate memory for initial temperature
    gsl_matrix* T1 = gsl_matrix_alloc(ny,nx);
    
    cout << "Soving for temperature distrubution in the domain for each time step" <<endl;
    
    // Soving for dT/dt+vx*dT/dx+vy*dT/dy=kappa*(d2T/dx2+d2T/dy2)
    // Composing matrix of coefficients mat()
    // and vector (column) of right parts b()
    // Process all grid points for Implicit Solving
    
    if (simul_type == "IMPLICIT") {
    implicit_T1 (To, nx, ny, dx, dy, diff, dt, left_condition, right_condition, top_condition, 
                bottom_condition, temp_left, T1, temp_right, temp_top, temp_bottom, total_time,
                vx, vy);
    } 
    else {
    explicit_T1 (To, nx, ny, dx, dy, diff , dt, left_condition, right_condition, top_condition, 
                bottom_condition, temp_left , T1, temp_right, temp_top, temp_bottom, total_time,
                vx, vy);
    }
    for (int i =0; i<ny; i++) {
        for (int j = 0; j < nx; j++) {
        cout << gsl_matrix_get (T1, i, j)<< endl;
       }
    }
    //generate output file in .vts format
    
    string dirname;
    
    write_vts(dirname, total_time, output_fre, X, Y,
            nx, ny, T1, vx, vy);

    std::cout << "Program runing time: "<<float( clock () - t1 ) / CLOCKS_PER_SEC<< endl;
    
    return 0;
    gsl_matrix_free (T1);
    gsl_matrix_free (To);
    gsl_matrix_free (vx);
    gsl_matrix_free (vy);
    gsl_matrix_free (rho_m);
}

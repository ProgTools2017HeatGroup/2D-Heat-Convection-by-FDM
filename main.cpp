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
#include "set_density.h"
#include "calculate_velocity.h"
#include "calculate_temperature.h"

using namespace std;
/**
 * @short Main program
 * @file  main.cpp
 * @author Arushi Saxena, Hao Lu, Jia Zhang
 * @return 0 on success
 *
 * The program aims to use finnite difference method to compute 2D heat
 * convection in a rectangular box.
 */

int main(int argc, char* argv[])
{
//    clock_t start, end;
//    start = clock();

    int opt;
    char *infile, *logfile;

    while ((opt = getopt(argc, argv, "i:o:hv")) != -1)
        switch (opt)
    {
        case 'h':
            cout << "usage: " << argv[0] << " [OPTIONS][-i] INPUTFILENAME;[-o] LOGFILENAME;[-h] HELP;[-v] VERSION" << endl;
            break;
        case 'v':
            cout << argv[0] << ": Solve 2D-heat-convection using finite differences method --ver1.00" << endl;
            break;
        case 'i':
            infile = optarg;
//            cout << "Inputfile is " << infile << endl;
//            if (strcmp(argv[optind+2], "-o") != 0)
//            {
//                cout << "Missing logfile option" << endl;
//                exit(EXIT_FAILURE);
//            }
            break;
        case 'o':
            logfile = optarg;
            cout << "Logfile is " << logfile << endl;
            break;
        case '?':
            if (optopt == 'i')
            {
                cout << "Missing inputfile option" <<endl;
                exit(EXIT_FAILURE);
            }
            else if (optopt == 'o')
            {
                cout << "Missing logfile option" << endl;
                exit(EXIT_FAILURE);
            }
            else
            {
                cout << "Unknown option" << endl;
                exit(EXIT_FAILURE);
            }
        default:
            abort();
    }

//    check_infile(argc);

    double rho, vis, diff, expa;
    int  xe, ye, nx, ny;
//    double **P, **T, **Vx, **Vy;
    string left_con, right_con, bottom_con, top_con, simul_type;
    int left_condition, right_condition, bottom_condition, top_condition;
    double temp_left, temp_right, temp_bottom, temp_top, Temp;
    double velo_left, velo_right, velo_bottom, velo_top, total_time, output_fre;
    vector<string> str;
 
    read_infile(infile, str);

   
    store_params(str, &rho, &vis, &diff, &expa, &xe, &ye, &nx, &ny, &left_con, &right_con, &bottom_con, &top_con,
        &left_condition, &right_condition, &bottom_condition, &top_condition, &temp_left, &temp_right, &temp_bottom,
        &temp_top, &velo_left, &velo_right, &velo_bottom, &velo_top, &Temp, &total_time, &output_fre, &simul_type);
 
    write_logfile(logfile, &rho, &vis, &diff, &expa, &xe, &ye, &nx, &ny, &left_con, &right_con, &bottom_con, &top_con,
        &left_condition, &right_condition, &bottom_condition, &top_condition, &temp_left, &temp_right, &temp_bottom,
        &temp_top, &velo_left, &velo_right, &velo_bottom, &velo_top, &Temp, &total_time, &output_fre, &simul_type);

    // get points in X and Y direction for printing in output
    int** X = generate_x_points (xe, ye, nx, ny);
    int** Y = generate_y_points (xe, ye, nx, ny);
    // get grid spacing to be used in later programs
    double dy = get_dy (ye, ny);
    double dx = get_dy (xe, nx);
    
    // allocate memory for initial temperature
    gsl_matrix* To = gsl_matrix_alloc(ny,nx);

    double back = 1300;
    set_back_value (To, ny, nx, back);
    double length = 12;
    double height = 10; 
    double coord_x = 5;
    double coord_y = 5;
    double perturb = 1500;
    string pertub_type = "box";
    double sigma = 13;
    double radius = 5;

    if (pertub_type == "box") {
        set_box (To, dx, dy, length, height, coord_x, coord_y, perturb, xe, ye);
    } else if (pertub_type == "disk") {
        set_disk (To, dx, dy, radius, coord_x, coord_y, perturb, xe, ye);
    }
    else if (pertub_type == "gaussian")  {
        set_gaussian (To, dx, dy, sigma, coord_x, coord_y, perturb, xe, ye);
    }

    // allocate memory for modified density
    gsl_matrix* rho_m = gsl_matrix_alloc(ny,nx);
    set_density (To, rho_m, back, expa, rho, nx, ny);
     
    // allocate memory for velocities
    gsl_matrix* vx = gsl_matrix_alloc(ny,nx);
    gsl_matrix* vy = gsl_matrix_alloc(ny,nx);

    set_horizontal_velocity (rho_m, nx, ny, vis, dx, dy, left_con, right_con, top_con, bottom_con, velo_left, 
            velo_right,  velo_top,  velo_bottom, vx);
    set_vertical_velocity (rho_m, nx, ny, vis, dx, dy, left_con, right_con, top_con, bottom_con, velo_left, 
            velo_right,  velo_top,  velo_bottom, vy);

    double dt = stable_time (xe, ye, nx, ny, diff, vx, vy, dx, dy);
     
    // allocate memory for initial temperature
    gsl_matrix* T1 = gsl_matrix_alloc(ny,nx);

    string simul_type = "IMPLICIT";
    if (simul_type == "IMPLICIT") {
    implicit_T1 (To, nx, ny, dx, dy, diff , dt, left_condition, right_condition, top_condition, 
                bottom_condition, temp_left , T1, temp_right, temp_top, temp_bottom, total_time,
                vx, vy);
    } 
    else {
    explicit_T1 (To, nx, ny, dx, dy, diff , dt, left_condition, right_condition, top_condition, 
                bottom_condition, temp_left , T1, temp_right, temp_top, temp_bottom, total_time,
                vx, vy);
    }
//    double time = (double)(end - start) / CLOCKS_PER_SEC;
//    cout << time << endl;

    return 0;
}

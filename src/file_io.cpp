/**
* @short   input and output
* @file    file_io.cpp
* @author  Jia Zhang
*
* This file contains the functions used for reading input file and store parameters
* and write into memory, login file and out to the screen.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "utility.h"

using namespace std;
//  output values in scientific form
using std::scientific;

/**
* Author:    Jia Zhang
*
* Description: This function read all characters from input file in string format.
* 
* Return     0 on success
*
* Return     EXIT_FAILURE when input file is nonexistent or cannot be opened.
*/

int read_infile(char* args, vector<string> &str)
{
    int i = 0;
    string s;
    ifstream infile;

    infile.open(args);
    if (!infile.is_open())
    {
        cout << "inputfile not found\n" << endl;
        exit(EXIT_FAILURE);
    }

    // Read variables as strings from infile
    while (infile >> s)
    {
        str.push_back(s);
        i++;
    }

    infile.close();

    return 0;
}

/**
* Author:    Jia Zhang
*
* Description: This function read all of parameters to memory in the declared types.
* It uses pass_vari() and check_vari() functions to store the parameters when they are reasonable.
*
* Return    0 on success
*
* Return    EXIT_FAILURE when the value of parameter is unreasonable.
*/

int store_params(vector<string> &str, double *rho, double *vis, double *diff, double *expa,
    int *xe, int *ye, int *nx, int *ny, string *left_con, string *right_con, string *bottom_con,
    string *top_con, int *left_condition, int *right_condition, int *bottom_condition, int *top_condition,
    double *temp_left, double *temp_right, double *temp_bottom, double *temp_top, double *velo_left,
    double *velo_right, double *velo_bottom, double *velo_top, double *Temp, string *pert_type, double *xo,
    double *yo, double *pert_T, double *length, double *width, double *radius, double *sigma, double *total_time,
    double *output_fre, string *simul_type)
{
    size_t i = 0;
    while ( i<str.size() )
    {
        pass_vari(str, i, "expansion_coefficient", expa);
        pass_vari(str, i, "temp_left_value", temp_left);
        pass_vari(str, i, "temp_right_value", temp_right);
        pass_vari(str, i, "temp_bottom_value", temp_bottom);
        pass_vari(str, i, "temp_top_value", temp_top);
        pass_vari(str, i, "velocity_left_value", velo_left);
        pass_vari(str, i, "velocity_right_value", velo_right);
        pass_vari(str, i, "velocity_bottom_value", velo_bottom);
        pass_vari(str, i, "velocity_top_value", velo_top);
        pass_vari(str, i, "Temperature", Temp);
        pass_vari(str, i, "xo", xo);
        pass_vari(str, i, "yo", yo);
        pass_vari(str, i, "length", length);
        pass_vari(str, i, "width", width);
        pass_vari(str, i, "perturbation_T", pert_T);
        pass_vari(str, i, "radius", radius);
        pass_vari(str, i, "sigma", sigma);
        pass_vari(str, i, "total_time", total_time);
        pass_vari(str, i, "output_frequency", output_fre);
        pass_vari(str, i, "simulation_type", simul_type);

        if (pass_vari(str, i, "density", rho) && check_vari(*rho, 0))  print_error();
        if (pass_vari(str, i, "viscosity", vis) && check_vari(*vis, 0)) print_error();
        if (pass_vari(str, i, "diffusivity", diff) && check_vari(*diff, 0)) print_error();
        if (pass_vari(str, i, "x_extend", xe) && check_vari(*xe, 0)) print_error();
        if (pass_vari(str, i, "y_extend", ye) && check_vari(*ye, 0)) print_error();
        if (pass_vari(str, i, "nx", nx) && check_vari(*nx, 0)) print_error();
        if (pass_vari(str, i, "ny", ny) && check_vari(*ny, 0)) print_error();

        if (pass_vari(str, i, "left_condition", left_con))
        {
            if (check_vari(*left_con, "NO_SLIP") && check_vari(*left_con, "FREE_SLIP"))  print_error();
        }
        if (pass_vari(str, i, "right_condition", right_con))
        {
            if (check_vari(*right_con, "NO_SLIP") && check_vari(*right_con, "FREE_SLIP"))  print_error();
        }
        if (pass_vari(str, i, "bottom_condition", bottom_con))
        {
            if (check_vari(*bottom_con, "NO_SLIP") && check_vari(*bottom_con, "FREE_SLIP"))  print_error();
        }
        if (pass_vari(str, i, "top_condition", top_con))
        {
            if (check_vari(*top_con, "NO_SLIP") && check_vari(*top_con, "FREE_SLIP"))  print_error();
        }
        if (pass_vari(str, i, "temp_left_condition", left_condition))
        {
            if (check_vari(*left_condition, 0) || !check_vari(*left_condition, 2)) print_error();
        }
        if (pass_vari(str, i, "temp_right_condition", right_condition))
        {
            if (check_vari(*right_condition, 0) || !check_vari(*right_condition, 2)) print_error();
        }
        if (pass_vari(str, i, "temp_bottom_condition", bottom_condition))
        {
            if (check_vari(*bottom_condition, 0) || !check_vari(*bottom_condition, 2)) print_error();
        }
        if (pass_vari(str, i, "temp_top_condition", top_condition))
        {
            if (check_vari(*top_condition, 0) || !check_vari(*top_condition, 2)) print_error();
        }
        if (pass_vari(str, i, "perturbation_type", pert_type))
        {
            if (check_vari(*pert_type, "BOX") && check_vari(*pert_type, "DISK")
                && check_vari(*pert_type, "GAUSSIAN"))   print_error();
        }
//        if (str[i] == "Temperature")
//        {
//            allocate_matrix(T, *nx, *ny);
//            read_matrix(str, i, T, nx, ny);
//        }
        i++;
    }
    return 0;
}

/**
* Author:    Jia Zhang
*
* Description: This function used for printing parameters into log file.
*
* Return     0 on success
*
*/

int write_logfile(char* args, double *rho, double *vis, double *diff, double *expa,
    int *xe, int *ye, int *nx, int *ny, string *left_con, string *right_con, string *bottom_con,
    string *top_con, int *left_condition, int *right_condition, int *bottom_condition, int *top_condition,
    double *temp_left, double *temp_right, double *temp_bottom, double *temp_top, double *velo_left,
    double *velo_right, double *velo_bottom, double *velo_top, double *Temp, string *pert_type, double *xo,
    double *yo, double *pert_T, double *length, double *width, double *radius, double *sigma, double *total_time,
    double *output_fre, string *simul_type)
{
    ofstream logfile;
    logfile.open(args);
    logfile << "density =\n" << scientific << *rho << endl;
    logfile << "viscosity =\n" << scientific << *vis << endl;
    logfile << "diffusivity=\n" << scientific << *diff << endl;
    logfile << "expansion_coefficient=\n" << scientific << *expa << endl;
    logfile << "x_extend = \n" << scientific << *xe << endl;
    logfile << "y_extend =\n" << scientific << *ye << endl;
    logfile << "nx =\n" << scientific << *nx << endl;
    logfile << "ny =\n" << scientific << *ny << endl;
    logfile << "left_condition =\n" << *left_con << endl;
    logfile << "right_condition =\n" << *right_con << endl;
    logfile << "bottom_condition =\n" << *bottom_con << endl;
    logfile << "top_condition =\n" << *top_con << endl;
    logfile << "temp_left_condition =\n" << scientific << *left_condition << endl;
    logfile << "temp_right_condition =\n" << scientific << *right_condition << endl;
    logfile << "temp_bottom_condition =\n" << scientific << *bottom_condition << endl;
    logfile << "temp_top_condition =\n" << scientific << *top_condition << endl;
    logfile << "temp_left_value =\n" << scientific << *temp_left << endl;
    logfile << "temp_right_value =\n" << scientific << *temp_left << endl;
    logfile << "temp_bottom_value =\n" << scientific << *temp_bottom << endl;
    logfile << "temp_top_value =\n" << scientific << *temp_top << endl;
    logfile << "velo_left_value =\n" << scientific << *velo_left << endl;
    logfile << "velo_right_value =\n" << scientific << *velo_left << endl;
    logfile << "velo_bottom_value =\n" << scientific << *velo_bottom << endl;
    logfile << "velo_top_value =\n" << scientific << *velo_top << endl;
    logfile << "Temp =\n" << scientific << *Temp << endl;
    logfile << "perturbation_type =\n" << *pert_type << endl;
    if (*pert_type == "BOX")
    {
        logfile << "xo =\n" << scientific << *xo << endl;
        logfile << "yo =\n" << scientific << *yo << endl;
        logfile << "length =\n" << scientific << *length << endl;
        logfile << "width =\n" << scientific << *width << endl;
        logfile << "perturbation_T =\n" << scientific << *pert_T << endl;
    }
    else if (*pert_type == "DISK")
    {
        logfile << "xo =\n" << scientific << *xo << endl;
        logfile << "yo =\n" << scientific << *yo << endl;
        logfile << "radius =\n" << scientific << *radius << endl;
        logfile << "perturbation_T =\n" << scientific << *pert_T << endl;
    }
    else if (*pert_type == "GAUSSIAN")
    {
        logfile << "xo =\n" << scientific << *xo << endl;
        logfile << "yo =\n" << scientific << *yo << endl;
        logfile << "sigma =\n" << scientific << *sigma << endl;
        logfile << "perturbation_T =\n" << scientific << *pert_T << endl;
    }
    logfile << "total_time =\n" << scientific << *total_time << endl;
    logfile << "output_frequency=\n" << scientific << *output_fre << endl;
    logfile << "simulation_type=\n" << *simul_type << endl;
//    int j, k;
//    logfile << "Temperature =\n";
//    for (j = 0; j < *nx; j = j + 1)
//    {
//        for (k = 0; k < *ny; k = k + 1)
//        {
//            logfile << scientific << (*T)[j][k] << "\t";
//        }
//        logfile << "\n";
//    }

    logfile.close();

    return 0;
}

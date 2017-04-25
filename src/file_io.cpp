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
#include "structs.h"

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

int store_params(vector<string> &str, Parameters *params)
{
    size_t i = 0;
    while (i<str.size())
    {
        pass_vari(str, i, "expansion_coefficient", &params->expa);
        pass_vari(str, i, "temp_left_value", &params->temp_left);
        pass_vari(str, i, "temp_right_value", &params->temp_right);
        pass_vari(str, i, "temp_bottom_value", &params->temp_bottom);
        pass_vari(str, i, "temp_top_value", &params->temp_top);
        pass_vari(str, i, "velocity_left_value", &params->velo_left);
        pass_vari(str, i, "velocity_right_value", &params->velo_right);
        pass_vari(str, i, "velocity_bottom_value", &params->velo_bottom);
        pass_vari(str, i, "velocity_top_value", &params->velo_top);
        pass_vari(str, i, "Temperature", &params->Temp);
        pass_vari(str, i, "xo", &params->xo);
        pass_vari(str, i, "yo", &params->yo);
        pass_vari(str, i, "length", &params->length);
        pass_vari(str, i, "width", &params->width);
        pass_vari(str, i, "perturbation_T", &params->pert_T);
        pass_vari(str, i, "radius", &params->radius);
        pass_vari(str, i, "sigma", &params->sigma);
        pass_vari(str, i, "total_time", &params->total_time);
        pass_vari(str, i, "output_frequency", &params->output_fre);
        pass_vari(str, i, "simulation_type", &params->simul_type);
        pass_vari(str, i, "output_path", &params->output_path);

        if (pass_vari(str, i, "density", &params->rho) && check_vari(params->rho, 0))  print_error();
        if (pass_vari(str, i, "viscosity", &params->vis) && check_vari(params->vis, 0)) print_error();
        if (pass_vari(str, i, "diffusivity", &params->diff) && check_vari(params->diff, 0)) print_error();
        if (pass_vari(str, i, "x_extend", &params->xe) && check_vari(params->xe, 0)) print_error();
        if (pass_vari(str, i, "y_extend", &params->ye) && check_vari(params->ye, 0)) print_error();
        if (pass_vari(str, i, "nx", &params->nx) && check_vari(params->nx, 0)) print_error();
        if (pass_vari(str, i, "ny", &params->ny) && check_vari(params->ny, 0)) print_error();

        if (pass_vari(str, i, "left_condition", &params->left_con))
        {
            if (check_vari(params->left_con, "NO_SLIP") && check_vari(params->left_con, "FREE_SLIP"))  print_error();
        }
        if (pass_vari(str, i, "right_condition", &params->right_con))
        {
            if (check_vari(params->right_con, "NO_SLIP") && check_vari(params->right_con, "FREE_SLIP"))  print_error();
        }
        if (pass_vari(str, i, "bottom_condition", &params->bottom_con))
        {
            if (check_vari(params->bottom_con, "NO_SLIP") && check_vari(params->bottom_con, "FREE_SLIP"))  print_error();
        }
        if (pass_vari(str, i, "top_condition", &params->top_con))
        {
            if (check_vari(params->top_con, "NO_SLIP") && check_vari(params->top_con, "FREE_SLIP"))  print_error();
        }
        if (pass_vari(str, i, "temp_left_condition", &params->left_condition))
        {
            if (check_vari(params->left_condition, 0) || !check_vari(params->left_condition, 2)) print_error();
        }
        if (pass_vari(str, i, "temp_right_condition", &params->right_condition))
        {
            if (check_vari(params->right_condition, 0) || !check_vari(params->right_condition, 2)) print_error();
        }
        if (pass_vari(str, i, "temp_bottom_condition", &params->bottom_condition))
        {
            if (check_vari(params->bottom_condition, 0) || !check_vari(params->bottom_condition, 2)) print_error();
        }
        if (pass_vari(str, i, "temp_top_condition", &params->top_condition))
        {
            if (check_vari(params->top_condition, 0) || !check_vari(params->top_condition, 2)) print_error();
        }
        if (pass_vari(str, i, "perturbation_type", &params->pert_type))
        {
            if (check_vari(params->pert_type, "BOX") && check_vari(params->pert_type, "DISK")
                && check_vari(params->pert_type, "GAUSSIAN"))   print_error();
        }
        //        if (str[i] == "Temperature")
        //        {
        //            allocate_matrix(T, *params->nx, *params->ny);
        //            read_matrix(str, i, T, params->nx, params->ny);
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

int write_logfile(char* args, Parameters *params)
{
    ofstream logfile;
    logfile.open(args);
    logfile << "density =\n" << scientific << params->rho << endl;
    logfile << "viscosity =\n" << scientific << params->vis << endl;
    logfile << "diffusivity =\n" << scientific << params->diff << endl;
    logfile << "expansion_coefficient =\n" << scientific << params->expa << endl;
    logfile << "x_extend = \n" << scientific << params->xe << endl;
    logfile << "y_extend =\n" << scientific << params->ye << endl;
    logfile << "nx =\n" << scientific << params->nx << endl;
    logfile << "ny =\n" << scientific << params->ny << endl;
    logfile << "left_condition =\n" << params->left_con << endl;
    logfile << "right_condition =\n" << params->right_con << endl;
    logfile << "bottom_condition =\n" << params->bottom_con << endl;
    logfile << "top_condition =\n" << params->top_con << endl;
    logfile << "temp_left_condition =\n" << scientific << params->left_condition << endl;
    logfile << "temp_right_condition =\n" << scientific << params->right_condition << endl;
    logfile << "temp_bottom_condition =\n" << scientific << params->bottom_condition << endl;
    logfile << "temp_top_condition =\n" << scientific << params->top_condition << endl;
    logfile << "temp_left_value =\n" << scientific << params->temp_left << endl;
    logfile << "temp_right_value =\n" << scientific << params->temp_left << endl;
    logfile << "temp_bottom_value =\n" << scientific << params->temp_bottom << endl;
    logfile << "temp_top_value =\n" << scientific << params->temp_top << endl;
    logfile << "velo_left_value =\n" << scientific << params->velo_left << endl;
    logfile << "velo_right_value =\n" << scientific << params->velo_left << endl;
    logfile << "velo_bottom_value =\n" << scientific << params->velo_bottom << endl;
    logfile << "velo_top_value =\n" << scientific << params->velo_top << endl;
    logfile << "Temp =\n" << scientific << params->Temp << endl;
    logfile << "perturbation_type =\n" << params->pert_type << endl;

    if (params->pert_type == "BOX")
    {
        logfile << "xo =\n" << scientific << params->xo << endl;
        logfile << "yo =\n" << scientific << params->yo << endl;
        logfile << "length =\n" << scientific << params->length << endl;
        logfile << "width =\n" << scientific << params->width << endl;
        logfile << "perturbation_T =\n" << scientific << params->pert_T << endl;
    }
    else if (params->pert_type == "DISK")
    {
        logfile << "xo =\n" << scientific << params->xo << endl;
        logfile << "yo =\n" << scientific << params->yo << endl;
        logfile << "radius =\n" << scientific << params->radius << endl;
        logfile << "perturbation_T =\n" << scientific << params->pert_T << endl;
    }
    else if (params->pert_type == "GAUSSIAN")
    {
        logfile << "xo =\n" << scientific << params->xo << endl;
        logfile << "yo =\n" << scientific << params->yo << endl;
        logfile << "sigma =\n" << scientific << params->sigma << endl;
        logfile << "perturbation_T =\n" << scientific << params->pert_T << endl;
    }

    logfile << "total_time =\n" << scientific << params->total_time << endl;
    logfile << "output_frequency =\n" << scientific << params->output_fre << endl;
    logfile << "simulation_type =\n" << params->simul_type << endl;
    logfile << "output_path=\n" << params->output_path << endl;
    //    int j, k;
    //    logfile << "Temperature =\n";
    //    for (j = 0; j < *params->nx; j = j + 1)
    //    {
    //        for (k = 0; k < *params->ny; k = k + 1)
    //        {
    //            logfile << scientific << (*T)[j][k] << "\t";
    //        }
    //        logfile << "\n";
    //    }

    logfile.close();

    return 0;
}

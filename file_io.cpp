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

int store_params(vector<string> &str, float *rho, float *vis, float *diff, float *expa,
    int *xe, int *ye, int *nx, int *ny, float ***P, float ***T, float ***Vx,
    float ***Vy)
{
    size_t i = 0;
    while ( i<str.size() )
    {
        if (str[i] == "density")
        {
            if (read_float(str, i, *rho) || check_vari_float(*rho,0))
            {
                print_error();
            }
        }
        if (str[i] == "viscosity")
        {
            if (read_float(str, i, *vis) || check_vari_float(*vis,0))
            {
                print_error();
            }
                
        }
        if (str[i] == "diffusivity")
        {
            if (read_float(str, i, *diff) || check_vari_float(*diff,0))
            {
                print_error();
            }
        }
        if (str[i] == "expansion_coefficient")
        {
            read_float(str, i, *expa);
        }
        if (str[i] == "x_extend")
        {
            if (read_int(str, i, *xe) || check_vari_int(*xe,0))
            {
                print_error();
            }
        }
        if (str[i] == "y_extend")
        {
            if (read_int(str, i, *ye) || check_vari_int(*ye,0))
            {
                print_error();
            }
        }
        if (str[i] == "nx")
        {
            if (read_int(str, i, *nx) || check_vari_int(*nx,0))
            {
                print_error();
            }
        }
        if (str[i] == "ny")
        {
            if (read_int(str, i, *ny) || check_vari_int(*ny,0))
            {
                print_error();
            }
        }
        if (str[i] == "Temperature")
        {
            allocate_matrix(T, *nx, *ny);
            read_matrix(str, i, T, nx, ny);
        }
        if (str[i] == "Velocity_X")
        {
            allocate_matrix(Vx, *nx, *ny);
            read_matrix(str, i, Vx, nx, ny);
        }
        if (str[i] == "Velocity_Y")
        {
            allocate_matrix(Vy, *nx, *ny);
            read_matrix(str, i, Vy, nx, ny);
        }
        i++;
    }
    return 0;
}

int write_logfile(char* args, float *rho, float *vis, float *diff,
    float *expa, int *xe, int *ye, int *nx, int *ny, float ***P, float ***T, float ***Vx,
    float ***Vy)
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
    int j, k;
    logfile << "Temperature =\n";
    for (j = 0; j < *nx; j = j + 1)
    {
        for (k = 0; k < *ny; k = k + 1)
        {
            logfile << scientific << (*T)[j][k] << "\t";
        }
        logfile << "\n";
    }
    logfile << "Velocity_X =\n";
    for (j = 0; j < *nx; j = j + 1)
    {
        for (k = 0; k < *ny; k = k + 1)
        {
            logfile << scientific << (*Vx)[j][k] << "\t";
        }
        logfile << "\n";
    }
    logfile << "Velocity_Y =\n";
    for (j = 0; j < *nx; j = j + 1)
    {
        for (k = 0; k < *ny; k = k + 1)
        {
            logfile << scientific << (*Vy)[j][k] << "\t";
        }
        logfile << "\n";
    }

    logfile.close();

    return 0;
}
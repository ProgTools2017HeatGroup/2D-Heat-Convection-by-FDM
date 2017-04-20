#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "file_io.h"
#include "check_input.h"

using namespace std;
//  output values in scientific form
using std::scientific;

int check_infile(int argc)
{
    if (argc < 3)
    {
        cout << "Missing inputfile or logfile, please check\n";
        return false;
    }
    else if (argc > 3)
    {
        cout << "Too many inputfiles, please check\n";
        return false;
    }
    else
    {
         cout << "The program is initializing......\n" << endl;
         return 0;
    }
}

int read_infile(int argc, char* argv[], string str[])
{
    int i = 0;
    string s;
    ifstream infile;

    infile.open(argv[1]);
    if (!infile.is_open())
    {
        cout << "inputfile not found\n" << endl;
        return false;
    }

    // Read variables as strings from infile
    while (infile >> s)
    {
        str[i] = s;
        i++;
    }

    infile.close();

    return 0;
}

int store_params(string str[], float *rho, float *vis, float *diff, float *expa,
    float *xe, float *ye, int *nx, int *ny, float ***P, float ***T, float ***Vx,
    float ***Vy)
{
    int i = 0;
    while (str[i] != "")
    {
        if (str[i] == "density")
        {
            read_float(str, i, *rho);
            check_input(str[i], *rho, 0);
        }
        if (str[i] == "viscosity")
        {
            read_float(str, i, *vis);
            check_input(str[i], *vis, 0);
        }
        if (str[i] == "diffusivity")
        {
            read_float(str, i, *diff);
            check_input(str[i], *diff, 0);
        }
        if (str[i] == "expansion_coefficient")
        {
            read_float(str, i, *expa);
            check_input(str[i], *expa, 0);
        }
        if (str[i] == "x_extend")
        {
            read_float(str, i, *xe);
            check_input(str[i], *xe, 0);
        }
        if (str[i] == "y_extend")
        {
            read_float(str, i, *ye);
            check_input(str[i], *ye, 0);
        }
        if (str[i] == "nx")
        {
            read_int(str, i, *nx);
            check_input(str[i], *nx, 0);
        }
        if (str[i] == "ny")
        {
            read_int(str, i, *ny);
            check_input(str[i], *ny, 0);
        }
        if (str[i] == "Pressure")
        {
            allocate_matrix(P, *nx, *ny);
            read_matrix(str, i, P, nx, ny);
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


int read_float(string str[], int i, float &float_value)
{

    cout << str[i] << "\t=" << endl;

    char* c;
    c = const_cast<char*>(str[i + 2].c_str());
    sscanf(c, "%e", &float_value);

    cout << scientific << float_value << endl << "\n";

    return 0;
}

int read_int(string str[], int i, int &int_value)
{

    cout << str[i] << "\t=" << endl;
    char* c;
    c = const_cast<char*>(str[i + 2].c_str());
    sscanf(c, "%d", &int_value);
    cout << scientific << int_value << endl << "\n";

    return 0;
}


int read_matrix(string str[], int i, float ***matr, int *nx, int *ny)
{

    cout << str[i] << "\t=" << endl;
    int j, k;
    char* c;
    for (j = 0; j < *nx; j = j + 1)
    {
        for (k = 0; k < *ny; k = k + 1)
        {
            c = const_cast<char*>(str[i + 2].c_str());
            sscanf(c, "%e", matr[j][k]);
            cout << scientific << matr[j][k] << "\t";
            i++;
        }
        cout << "\n";
    }
    cout << "\n";

    return 0;
}


int allocate_matrix(float ***M, int nx, int ny)
{
    int i;
    (*M) = (float**)malloc(sizeof(float*)*nx);
    if (*M == NULL)
        return 1;

    for (i = 0; i<nx; i++) {
        (*M)[i] = (float*)malloc(sizeof(float)*ny);
        if ((*M)[i] == NULL)
            return 1;
    }
    return 0;
}

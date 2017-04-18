#ifndef FILE_IO_H_
#define FILE_IO_H_

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <cmath>
#include <cstdlib>

using namespace std;

int check_infile(int argc);
int read_infile(int argc, char* argv[], string str[]);
int store_params(string str[], float *rho, float *vis, float *diff, float *expa,
    float *xe, float *ye, int *nx, int *ny, float ***P, float ***T, float ***Vx,
    float ***Vy);
//int write_input
int read_float(string str[], int i, float &float_value);
int read_int(string str[], int i, int &int_value);
int read_matrix(string str[], int i, float ***matr, int *nx, int *ny);
int allocate_matrix(float ***M, int nx, int ny);


#endif

#ifndef FILE_IO_H_
#define FILE_IO_H_

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <cstdlib>

using namespace std;

int read_infile(char* args, vector<string> &str);
int store_params(vector<string> &str, double *rho, double *vis, double *diff, double *expa,
    int *xe, int *ye, int *nx, int *ny, string *left_con, string *right_con, string *bottom_con,
    string *top_con, int *left_condition, int *right_condition, int *bottom_condition, int *top_condition,
    double *temp_left, double *temp_right, double *temp_bottom, double *temp_top, double *velo_left,
    double *velo_right, double *velo_bottom, double *velo_top, double *Temp, string *pert_type, double *xo,
    double *yo, double *pert_T, double *length, double *width, double *radius, double *sigma, double *total_time,
    double *output_fre, string *simul_type);
int write_logfile(char* args, double *rho, double *vis, double *diff, double *expa,
    int *xe, int *ye, int *nx, int *ny, string *left_con, string *right_con, string *bottom_con,
    string *top_con, int *left_condition, int *right_condition, int *bottom_condition, int *top_condition,
    double *temp_left, double *temp_right, double *temp_bottom, double *temp_top, double *velo_left,
    double *velo_right, double *velo_bottom, double *velo_top, double *Temp, string *pert_type, double *xo,
    double *yo, double *pert_T, double *length, double *width, double *radius, double *sigma, double *total_time,
    double *output_fre, string *simul_type);



#endif

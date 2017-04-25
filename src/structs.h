#ifndef STRUCTS_H_
#define STRUCTS_H_

#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <cmath>

using namespace std;

struct Parameters
{
    int  xe, ye, nx, ny;
    int left_condition, right_condition, bottom_condition, top_condition;
    double rho, vis, diff, expa;
    double temp_left, temp_right, temp_bottom, temp_top, Temp;
    double velo_left, velo_right, velo_bottom, velo_top;
    double total_time, output_fre;
    double xo, yo, pert_T, length, width, radius, sigma;
    string left_con, right_con, bottom_con, top_con, pert_type, simul_type, output_path;
};

#endif
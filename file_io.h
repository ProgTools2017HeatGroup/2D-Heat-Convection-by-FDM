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
    int *xe, int *ye, int *nx, int *ny, double ***T, double ***Vx,
    double ***Vy);
int write_logfile(char* agrs, double *rho, double *vis, double *diff,
    double *expa, int *xe, int *ye, int *nx, int *ny, double ***T, double ***Vx,
    double ***Vy);

#endif

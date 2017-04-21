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
int store_params(vector<string> &str, float *rho, float *vis, float *diff, float *expa,
    int *xe, int *ye, int *nx, int *ny, float ***P, float ***T, float ***Vx,
    float ***Vy);
int write_logfile(char* agrs, float *rho, float *vis, float *diff,
    float *expa, int *xe, int *ye, int *nx, int *ny, float ***P, float ***T, float ***Vx,
    float ***Vy);

#endif

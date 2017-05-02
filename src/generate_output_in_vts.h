/**
 * @Header for output generation function
 * @File  generate_output_in_vts.h
 *
 * This file contains the prototype of function used for generating the .vts file
 *
 */

#ifndef OUTPUT_VTS
#define OUTPUT_VTS
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <gsl/gsl_matrix.h>
using namespace std;


void write_vts(string dirname, int** X, int** Y, double t,
              int nx, int ny, gsl_matrix* T, gsl_matrix* Vx, gsl_matrix* Vy);
#endif

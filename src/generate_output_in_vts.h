#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <gsl/gsl_matrix.h>
using namespace std;


int write_vts(string dirname, double total_time, double freq,  int** X, int** Y,
              int nx, int ny, gsl_matrix* T, gsl_matrix* Vx, gsl_matrix* Vy);

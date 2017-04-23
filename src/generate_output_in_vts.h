#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <direct.h>
#include <gsl/gsl_matrix.h>
using namespace std;


int write_vts(string dirname, double dx, double dy, double x_ext, double y_ext, int time_step,
              int nx, int ny, gsl_matrix* T, gsl_matrix* Vx, gsl_matrix* Vy);

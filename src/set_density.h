#ifndef DENSITY_H
#define DENSITY_H

#include <gsl/gsl_matrix.h>
#include <iostream>

using namespace std;

void set_density (gsl_matrix* T_o, gsl_matrix* rho, double T_pert, double alpha, double rho_o, int nx, int ny);

#endif

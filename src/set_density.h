#ifndef DENSITY_H
#define DENSITY_H

#include <gsl/gsl_matrix.h>
#include <iostream>
#include "structs.h"

using namespace std;

void set_density (gsl_matrix* T_o, gsl_matrix* rho, Parameters *params);

#endif

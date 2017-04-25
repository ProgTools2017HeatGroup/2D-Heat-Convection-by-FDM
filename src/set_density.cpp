#include <gsl/gsl_matrix.h>
#include <iostream>
#include "structs.h"

using namespace std;

void set_density (gsl_matrix* T_o, gsl_matrix* rho, Parameters *params) {
    
    double T_pert = params->pert_T;
    double alpha = params->expa;
    double nx = params->nx;
    double ny = params->ny;
    double rho_o = params->rho;

    for (int i =0; i < ny; i++) {
        for (int j = 0; j < nx; j++) {
            gsl_matrix_set(rho, i, j, rho_o*(1- alpha*(gsl_matrix_get(T_o, i, j) - T_pert)));
        }
    }
    
}

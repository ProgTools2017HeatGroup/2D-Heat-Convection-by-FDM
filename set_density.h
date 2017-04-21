#include <gsl/gsl_matrix.h>
#include <iostream>

using namespace std;

void set_density (gsl_matrix* T_o, double Tback, double alpha, double rho_o, int nx, int ny) {
    gsl_matrix* rho = gsl_matrix_alloc(ny,nx);
    for (int i =0; i < ny; i++){
        for (int j = 0; j < nx; j++){
            gsl_matrix_set(rho, i, j, rho_o*(1- alpha*(gsl_matrix_get(T_o, i, j) - Tback)));
        }
    }
}

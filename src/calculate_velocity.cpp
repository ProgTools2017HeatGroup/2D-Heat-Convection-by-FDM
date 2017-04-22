#include <iostream>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include "calculate_velocity.h"

void set_horizontal_velocity (gsl_matrix* rho, int nx, int ny, double eta, double dx, double dy, string left_condition,
                string right_condition, string top_condition, string bottom_condition, double left_velocity,
                double right_velocity, double top_velocity, double bottom_velocity, gsl_matrix* horizontal_velocity) {

    gsl_vector *x = gsl_vector_alloc (ny*nx);
    set_omega (rho, x, nx, ny, eta, dx, dy);

    gsl_matrix* psi = gsl_matrix_alloc (ny, nx);
    set_psi (psi, x, nx, ny, dx, dy, left_condition, right_condition, top_condition,
            bottom_condition, left_velocity, right_velocity, top_velocity, bottom_velocity);

    for (int i = 0; i < ny ; i++) {
	    for (int j = 0; j < nx ; j++) {
            gsl_matrix_set(horizontal_velocity, i, j, (gsl_matrix_get(psi, i+1, j) -
	        gsl_matrix_get(psi, i-1, j)/(2*dy)));
	    }
    }
    gsl_vector_free (x);
    gsl_matrix_free (psi);
}

void set_vertical_velocity (gsl_matrix* rho, int nx, int ny, double eta, double dx, double dy, string left_condition,
                string right_condition, string top_condition, string bottom_condition, double left_velocity,
                double right_velocity, double top_velocity, double bottom_velocity, gsl_matrix* vertical_velocity) {

    gsl_vector *x = gsl_vector_alloc (ny*nx);
    set_omega (rho,  x, nx, ny, eta, dx, dy);

    gsl_matrix* psi = gsl_matrix_alloc (ny, nx);
    set_psi (psi, x, nx, ny, dx, dy, left_condition, right_condition, top_condition, bottom_condition, 
            left_velocity, right_velocity, top_velocity, bottom_velocity);

    for (int i = 0; i < ny ; i++) {
	    for (int j = 0; j < nx ; j++) {
            gsl_matrix_set(vertical_velocity, i, j, -(gsl_matrix_get(psi, i, j+1) -
	        gsl_matrix_get(psi, i, j-1)/(2*dx)));
	    }
    }
    gsl_vector_free (x);
    gsl_matrix_free (psi);
}

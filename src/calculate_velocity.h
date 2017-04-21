#ifndef CALCULATE_VELOCITY_H
#define CALCULATE_VELOCITY_H

#include <iostream>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <string>

using namespace std;
// Solving Poisson equation for vorticity  d2OMEGA/dx2+d2OMEGA/dy2=gy*dRHO/dx
// Composing matrix of coefficients A()  and vector (column) of right parts b()
// Boundary conditions: OMEGA=0 ; Process all Grid points

void set_omega (gsl_matrix* rho, gsl_vector* x, int nx, int ny, double eta, double dx, double dy) {

    const double GRAVITY = 9.8;
    int s;
    // Allocate  matrix A in Ax = b
    gsl_matrix* A = gsl_matrix_alloc (ny*nx, ny*nx);
    // Allocate  right side of vector , b
    gsl_vector* b   = gsl_vector_calloc (ny*nx);
    // Allocate p for LU decomposition
    gsl_permutation* p = gsl_permutation_alloc (ny*nx);

    for (int i = 0; i < ny; i++) {
	    for (int j = 0; j < nx; j++) {
	// Global index for current node
	    int k = (j*ny) + i;
	// Boundary condition at nodes, b = 0 at boundaries
	    if (i == 0 || i == ny - 1 || j == 0 || j == nx - 1) {
	        gsl_matrix_set (A, k, k, 1);
	    }

	    // Internal nodes
	    else {
	    // A matrix
	        gsl_matrix_set (A, k, k - ny, (1.0/dx)*(1.0/dx));
	        gsl_matrix_set (A, k, k - 1, (1.0/dy)*(1.0/dy));
	        gsl_matrix_set (A, k, k, -2.0/(dx*dx) -2.0/(dy*dy));
	        gsl_matrix_set (A, k, k+1, (1.0/dy)*(1.0/dy));
	        gsl_matrix_set (A, k, k + ny, (1.0/dx)*(1.0/dx));
	    // b vector
	        gsl_vector_set (b, k, (GRAVITY/eta)*(gsl_matrix_get(rho, j+1, i) - gsl_matrix_get(rho, j-1, i))/(2*dx));
	        }
	    }
    }
    // Obtain vector of solutions x = (A^-1)*b
    gsl_linalg_LU_decomp (A, p, &s);
    gsl_linalg_LU_solve (A, p, b, x);

    gsl_permutation_free (p);
    gsl_vector_free (b);
    gsl_matrix_free(A);
}

// Solving Poisson equation for stream function d2PSI/dx2+d2PSI/dy2=OMEGA, same A matrix as before

void set_psi (gsl_matrix* psi, gsl_vector* x, int nx, int ny, double dx, double dy, string left_condition,
                string right_condition, string top_condition, string bottom_condition, double left_velocity,
                double right_velocity, double top_velocity, double bottom_velocity) {

    int s;
    // Allocate  matrix A in Ax = b
    gsl_matrix* A = gsl_matrix_alloc (ny*nx, ny*nx);
    // Allocate p for LU decomposition
    gsl_permutation* p = gsl_permutation_alloc (ny*nx);

    // Process internal nodes
    for (int i = 1; i < ny-1; i++) {
	    for (int j = 1; j < nx-1; j++) {
	// Global index for current node
	        int k = (j*ny) + i;
	        if (j == 0 ) {
                if (left_condition != "FREE_SLIP") {
                    gsl_matrix_set (A, k, k, 1);
                    gsl_vector_set (x, k, 0);
                }
                else {
                    gsl_matrix_set (A, k, k, 1);
                    gsl_vector_set (x, k, -left_velocity*dx);
                }
            }
            else if (j == nx - 1 ) {
                if (right_condition != "FREE_SLIP") {
                    gsl_matrix_set (A, k, k, 1);
                    gsl_vector_set (x, k, 0);
                }
                else {
                    gsl_matrix_set (A, k, k, 1);
                    gsl_vector_set (x, k, -right_velocity*dx);
                }
            }

             else if (i == 0 && j > 0 && j < nx - 1) {
                if (top_condition != "FREE_SLIP") {
                    gsl_matrix_set (A, k, k, 1);
                    gsl_vector_set (x, k, 0);
                }
                else {
                    gsl_matrix_set (A, k, k, 1);
                    gsl_vector_set (x, k, top_velocity*dy);
                }
            }

             else if (i == ny - 1 && j > 0 && j < nx - 1) {
                if (bottom_condition != "FREE_SLIP") {
                    gsl_matrix_set (A, k, k, 1);
                    gsl_vector_set (x, k, 0);
                }
                else {
                    gsl_matrix_set (A, k, k, 1);
                    gsl_vector_set (x, k, bottom_velocity*dy);
                }
            }

	    // Internal nodes
            else {
            // A matrix
                gsl_matrix_set (A, k, k - ny, (1.0/dx)*(1.0/dx));
                gsl_matrix_set (A, k, k - 1, (1.0/dy)*(1.0/dy));
                gsl_matrix_set (A, k, k, -2.0/(dx*dx) -2.0/(dy*dy));
                gsl_matrix_set (A, k, k+1, (1.0/dy)*(1.0/dy));
                gsl_matrix_set (A, k, k + ny, (1.0/dx)*(1.0/dx));
            }
        }
    }

    gsl_vector *y = gsl_vector_alloc (ny*nx);
    gsl_linalg_LU_decomp (A, p, &s);
    gsl_linalg_LU_solve (A, p, x, y);

    // Reload solutions S() to 2D stream function array PSI()
    for (int i = 0; i < ny; i++) {
	    for (int j = 0; j < nx; j++) {
	        int k = (j*ny) + i;
	        gsl_matrix_set (psi, i, j, gsl_vector_get(y, k));
	    }
    }
    gsl_matrix_free(A);
    gsl_permutation_free (p);
}

void set_horizontal_velocity (gsl_matrix* rho, int nx, int ny, double eta, double dx, double dy, string left_condition,
                string right_condition, string top_condition, string bottom_condition, double left_velocity,
                double right_velocity, double top_velocity, double bottom_velocity, gsl_matrix* horizontal_velocity);

void set_vertical_velocity (gsl_matrix* rho, int nx, int ny, double eta, double dx, double dy, string left_condition,
                string right_condition, string top_condition, string bottom_condition, double left_velocity,
                double right_velocity, double top_velocity, double bottom_velocity, gsl_matrix* vertical_velocity);
#endif
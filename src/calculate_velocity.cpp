#include <iostream>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include "calculate_velocity.h"

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
                double right_velocity, double top_velocity, double bottom_velocity) 
{
    int s;
    // Allocate  matrix A in Ax = b
    gsl_matrix* A = gsl_matrix_alloc (ny*nx, ny*nx);
    // Allocate p for LU decomposition
    gsl_permutation* p = gsl_permutation_alloc (ny*nx);

    // Process all nodes
    for (int i = 0; i < ny; i++) {
	    for (int j = 0; j < nx; j++) {
	// Global index for current node
	        int k = (j*ny) + i;

            if (i == 0 || i == ny - 1 || j == 0 || j == nx - 1) {             
                if (j == 0 && left_condition == "NO_SLIP") {
                    gsl_matrix_set (A, k, k, 1);
                    gsl_vector_set (x, k, 0);
                }
                else if (j == 0 && left_condition == "FREE_SLIP") {
                    gsl_matrix_set (A, k, k, 1);
                    gsl_vector_set (x, k, -left_velocity*dx);
                }
                
                else if (j == nx - 1 && right_condition == "NO_SLIP") {
                    gsl_matrix_set (A, k, k, 1);
                    gsl_vector_set (x, k, 0);
                }
                else if (j == nx - 1 && right_condition == "FREE_SLIP") {
                    gsl_matrix_set (A, k, k, 1);
                    gsl_vector_set (x, k, -right_velocity*dx);
                }
                else if (i == 0 && j > 0 && j < nx - 1 && top_condition == "NO_SLIP") {
                    gsl_matrix_set (A, k, k, 1);
                    gsl_vector_set (x, k, 0);
                }
                else if (i == 0 && j > 0 && j < nx - 1 && top_condition == "FREE_SLIP") {
                    gsl_matrix_set (A, k, k, 1);
                    gsl_vector_set (x, k, top_velocity*dy);
                }
                else if (i == ny - 1 && j > 0 && j < nx - 1 && bottom_condition == "NO_SLIP") {
                    gsl_matrix_set (A, k, k, 1);
                    gsl_vector_set (x, k, 0);
                }
                else if (i == ny - 1 && j > 0 && j < nx - 1 && bottom_condition == "FREE_SLIP") {
                    gsl_matrix_set (A, k, k, 1);
                    gsl_vector_set (x, k, bottom_velocity*dy);
                }
            }

	    // Internal nodes
            else {
            // A matrix
                gsl_matrix_set (A, k, k - ny, (1/dx)*(1/dx));
                gsl_matrix_set (A, k, k - 1, (1./dy)*(1.0/dy));
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
                double right_velocity, double top_velocity, double bottom_velocity, gsl_matrix* horizontal_velocity) 
{
    gsl_vector *x = gsl_vector_alloc (ny*nx);
    set_omega (rho, x, nx, ny, eta, dx, dy);

    gsl_matrix* psi = gsl_matrix_alloc (ny, nx);
    set_psi (psi, x, nx, ny, dx, dy, left_condition, right_condition, top_condition,
            bottom_condition, left_velocity, right_velocity, top_velocity, bottom_velocity);
    
    for (int i = 0; i < ny ; i++) {
	    for (int j = 0; j < nx ; j++) {
            if (i == 0) {
                gsl_matrix_set(horizontal_velocity, i, j, (gsl_matrix_get(psi, i+1, j) -
                gsl_matrix_get(psi, i, j)/(dy)));
            }
            else if (i == ny-1) {
                gsl_matrix_set(horizontal_velocity, i, j, (gsl_matrix_get(psi, i, j) -
                gsl_matrix_get(psi, i-1, j)/(dy)));
            }
            else {
                gsl_matrix_set(horizontal_velocity, i, j, (gsl_matrix_get(psi, i+1, j) -
                gsl_matrix_get(psi, i-1, j)/(2*dy)));
            }
	    }
    }   
    gsl_vector_free (x);
    gsl_matrix_free (psi);
}

void set_vertical_velocity (gsl_matrix* rho, int nx, int ny, double eta, double dx, double dy, string left_condition,
                string right_condition, string top_condition, string bottom_condition, double left_velocity,
                double right_velocity, double top_velocity, double bottom_velocity, gsl_matrix* vertical_velocity) 
{
    gsl_vector *x = gsl_vector_alloc (ny*nx);
    set_omega (rho,  x, nx, ny, eta, dx, dy);
    gsl_matrix* psi = gsl_matrix_alloc (ny, nx);
    set_psi (psi, x, nx, ny, dx, dy, left_condition, right_condition, top_condition, bottom_condition, 
            left_velocity, right_velocity, top_velocity, bottom_velocity);

    for (int i = 0; i < ny ; i++) {
	    for (int j = 0; j < nx ; j++) {
            if (j == 0) {
                gsl_matrix_set(vertical_velocity, i, j, -(gsl_matrix_get(psi, i, j) -
                gsl_matrix_get(psi, i, j+1)/(dx)));
            }
            else if (j == nx-1) {
                gsl_matrix_set(vertical_velocity, i, j, (gsl_matrix_get(psi, i, j) -
                gsl_matrix_get(psi, i, j-1)/(dx)));
            }
            else {
                gsl_matrix_set(vertical_velocity, i, j, (gsl_matrix_get(psi, i, j+1) -
                gsl_matrix_get(psi, i, j-1)/(2*dx)));
            }
	    }
    }
    gsl_vector_free (x);
    gsl_matrix_free (psi);
}

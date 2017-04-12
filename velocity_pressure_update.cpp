/*
 * Used to calculate initial velocity using Vorticity-Stream Function formulation
 * April, 2017
 *
 */
#include <iostream>
#include <gsl/gsl_matrix.h>
//#include <gsl/matrix.h>
#include <gsl/gsl_linalg.h>

int points_in_y = 40;
int points_in_x = 40;
float dx = 1;
float dy = 1;

using namespace std;

int main () {
    double GRAVITY = 9.8;
    double eta = 1000;
    int s;
    // Allocate  matrix A in Ax = b
    gsl_matrix* mat = gsl_matrix_alloc (points_in_y*points_in_x, points_in_y*points_in_x);
    // Allocate  right side of vector , b
    gsl_vector* b   = gsl_vector_calloc (points_in_y*points_in_x);
    // Allocate density values at all nodes
    gsl_matrix* rho = gsl_matrix_calloc (points_in_y, points_in_x);
    // Allocate p for LU decomposition 
    gsl_permutation* p = gsl_permutation_alloc (points_in_y*points_in_x);

    // test values for density to run this program
    for (int i = 0; i < points_in_y; i++) {
	for (int j = 0; j < points_in_x; j++) {
            if (i/2 < 1) {
                 gsl_matrix_set(rho, i, j, 5000.0);
            }
            else {
                 gsl_matrix_set(rho, i, j, 3600.0);
            }
        }
    }

    // Populate A and b 
    for (int i = 0; i < points_in_y; i++) {
	for (int j = 0; j < points_in_x; j++) {
	// Global index for current node
	int k = (i*points_in_y) + j;  
	// Boundary condition at nodes 
	    if (i == 0 || i == points_in_y - 1 || j == 0 || j == points_in_x - 1) {
	    gsl_matrix_set (mat, k, k, 1);
	    }
            
	    // Internal nodes
	    else {
	    // A matrix
	    gsl_matrix_set (mat, k, k - points_in_y, (1.0/dx)*(1.0/dx));
	    gsl_matrix_set (mat, k, k - 1, (1.0/dy)*(1.0/dy));
	    gsl_matrix_set (mat, k, k, -2.0/(dx*dx) -2.0/(dy*dy));
	    gsl_matrix_set (mat, k, k+1, (1.0/dy)*(1.0/dy));
	    gsl_matrix_set (mat, k, k + points_in_y, (1.0/dx)*(1.0/dx));
	    // b vector
	    gsl_vector_set (b, k, (GRAVITY/eta)*(gsl_matrix_get(rho, j+1, i) - gsl_matrix_get(rho, j-1, i))/(2*dx));
	    } 	
	}           
    }
    // Obtain vector of solutions x = (A^-1)*b
    gsl_vector *x = gsl_vector_alloc (points_in_y*points_in_x);
    gsl_linalg_LU_decomp (mat, p, &s);
    gsl_linalg_LU_solve (mat, p, b, x);
         
    cout << gsl_vector_get(b, 2) << "\n";
    // Allocate memory for Vorticity
    gsl_matrix* omega = gsl_matrix_alloc (points_in_y, points_in_x);
    // Reload solutions S() to 2D vorticity array OMEGA()
    for (int i = 0; i < points_in_y; i++) {
	for (int j = 0; j < points_in_x; j++) {
	int k = (i*points_in_y) + j;
	gsl_matrix_set (omega, i, j, gsl_vector_get(x, k));  
	}
    }
    
    // Solving Poisson equation for stream function
    // d2PSI/dx2+d2PSI/dy2=OMEGA, 
    
    gsl_vector *y = gsl_vector_alloc (points_in_y*points_in_x);
    gsl_linalg_LU_decomp (mat, p, &s);
    gsl_linalg_LU_solve (mat, p, x, y);
    
   cout << gsl_vector_get(y, 4) << "\n";

    // Allocate memory for Stream function
    gsl_matrix* psi = gsl_matrix_alloc (points_in_y, points_in_x);
    // Reload solutions S() to 2D vorticity array OMEGA()
    for (int i = 0; i < points_in_y; i++) {
	for (int j = 0; j < points_in_x; j++) {
	int k = (i*points_in_y) + j;
	gsl_matrix_set (psi, i, j, gsl_vector_get(y, k));  
	}
    }
    
    // Compute vx,vy for internal nodes
    gsl_matrix* horizontal_velocity = gsl_matrix_alloc (points_in_y, points_in_x);
    gsl_matrix* vertical_velocity   = gsl_matrix_alloc (points_in_y, points_in_x);
    // Process internal Grid points
    for (int i = 1; i < points_in_y - 1; i++) {
	for (int j = 1; j < points_in_x - 1; j++) {
	gsl_matrix_set(horizontal_velocity, i, j, (gsl_matrix_get(psi, i+1, j) - 
	gsl_matrix_get(psi, i-1, j)/(2*dy)));
	gsl_matrix_set(vertical_velocity, i, j, -(gsl_matrix_get(psi, i, j+1) - 
	gsl_matrix_get(psi, i, j-1)/(2*dx))); 
	}
    }

// test for the output of the code
    for (int i = 1; i < points_in_y - 1; i++) {
	for (int j = 1; j < points_in_x - 1; j++) {
	cout << gsl_matrix_get(horizontal_velocity, i, j) << "\n";
	}
    }

    // free memory
    gsl_permutation_free (p);
    gsl_vector_free (x);
    gsl_vector_free (y);
    gsl_matrix_free (mat);
    gsl_matrix_free (rho);
    gsl_matrix_free (omega);
    gsl_matrix_free (psi);

    return 0;
}                           

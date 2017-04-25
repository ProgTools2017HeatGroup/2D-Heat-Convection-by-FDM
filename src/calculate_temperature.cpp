#include <iostream>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <math.h>
#include <cassert>
#include <string>
#include "calculate_temperature.h"
#include "structs.h"
#include "generate_output_in_vts.h"

void implicit_T1 (gsl_matrix* To, gsl_matrix* T1, double dx, double dy, gsl_matrix* vx, gsl_matrix* vy, 
                  double dt, Parameters *params, int** X, int **Y) {
    
    int nx = params->nx;
    int ny = params->ny;
    double kappa = params->diff;
    int left_condition = params->left_condition;
    int right_condition = params->right_condition;
    int top_condition = params->top_condition;
    int bottom_condition = params->bottom_condition;
    double left_temp = params->temp_left;
    double right_temp = params->temp_right;
    double top_temp = params->temp_top;
    double bottom_temp = params->temp_bottom;
    double total_time = params->total_time;
    string output_path = params->output_path;
    double freq = round(params->output_fre);

    int tnum = round(total_time/dt); // number of time steps
    for (int t = 1; t <= tnum; t++) {
        // Allocate  matrix A in Ax = b
        gsl_matrix* mat = gsl_matrix_alloc (ny*nx, ny*nx);
        // Allocate  right side of vector , b
        gsl_vector* b   = gsl_vector_calloc (ny*nx);
        int s;
        // soving for dT/dt+vx*dT/dx+vy*dT/dy=kappa*(d2T/dx2+d2T/dy2)
        // Composing matrix of coefficients mat()
        // and vector (column) of right parts b()
        // Process all grid points for Implicit Solving
        for (int i = 0; i < ny; i++) {
            for (int j = 0; j < nx; j++) {
                int k = (j*ny) + i;

                if (i == 0 || i == ny - 1 || j == 0 || j == nx - 1) {
                    // Upper Boundary
                    if (i == 0) {
                        switch (top_condition) {
                            case 0:
                                gsl_matrix_set (mat, k, k, 1);
                                gsl_matrix_set (mat, k, k+1, -1);
                                gsl_vector_set (b, k, 0);
                            case 1:
                                gsl_matrix_set (mat, k, k, 1);
                                gsl_vector_set (b, k, top_temp);
                            }
                        }
                   // Bottom boundary
                    else if (i == ny - 1) {
                        switch (bottom_condition) {
                            case 0:
                                gsl_matrix_set (mat, k, k, 1);
                                gsl_matrix_set (mat, k, k-1, -1);
                                gsl_vector_set (b, k, 0);
                            case 1:
                                gsl_matrix_set (mat, k, k, 1);
                                gsl_vector_set (b, k, bottom_temp);
                            }
                        }
                    // left condition

                    else if (j == 0 && i > 0 && i < ny - 1){
                        switch (left_condition) {
                            case 0:
                                gsl_matrix_set (mat, k, k, 1);
                                gsl_matrix_set (mat, k, k + ny, -1);
                                gsl_vector_set (b, k, 0);
                            case 1:
                                gsl_matrix_set (mat, k, k, 1);
                                gsl_vector_set (b, k, left_temp);
                            }
                        }
                   //risht condition
                    else if (j == nx - 1 && i > 0 && i < ny - 1) {
                        switch (right_condition) {
                            case 0:
                                gsl_matrix_set (mat, k, k, 1);
                                gsl_matrix_set (mat, k, k - ny, -1);
                                gsl_vector_set (b, k, 0);
                            case 1:
                                gsl_matrix_set (mat, k, k, 1);
                                gsl_vector_set (b, k, right_temp);
                            }
                        }
                    }
                // Internal nodes, matrix A

                else {
                        /* dT/dt-kappa*(d2T/dx2+d2T/dy2) = vx*dT/dx+vy*dT/dy
                        Tnew(i)/dt-kappa*(Tnew(i,j-1)-2*Tnew(i,j)+Tnew(i,j+1))/dx^2-
                        -kappa*(Tnew(i-1,j)-2*Tnew(i,j)+Tnew(i+1,j))/dy^2=
                        =Told(i,j)/dt-vx*dT/dx-vy*dT/dy
                        */
                    gsl_matrix_set (mat, k, k - ny, (-kappa/dx)*kappa/dx); // coefficient for T(i,j-1)
                    gsl_matrix_set (mat, k, k + ny, (-kappa/dx)*kappa/dx); // coefficient for T(i,j+1)
                    gsl_matrix_set (mat, k, k + 1, (-kappa/dy)*kappa/dy);  // coefficient for T(i+1,j)
                    gsl_matrix_set (mat, k, k - 1, (-kappa/dy)*kappa/dy);  // coefficient for T(i-1,j)
                    gsl_matrix_set (mat, k, k, (2*kappa/dy)*kappa/dy + (2*kappa/dy)*kappa/dy + 1/dt); // T(i,j)
                    // Internal nodes, vector b
                    gsl_vector_set (b, k, gsl_matrix_get(To, i, j)/dt);
                    // Add advective terms -vx*dT/dx
                    if (gsl_matrix_get (vx, i, j) > 0) {
                        gsl_vector_set(b, k, (gsl_vector_get (b, k) - gsl_matrix_get (vx, i, j)*(gsl_matrix_get(To, i, j)-
                        gsl_matrix_get(To, i, j-1))/dx));
                    }
                    else {
                        gsl_vector_set(b, k, (gsl_vector_get (b, k) - gsl_matrix_get (vx, i, j)*(gsl_matrix_get(To, i, j+1)-
                        gsl_matrix_get(To, i, j))/dx));
                    }
                    // -vy*dT/dy
                    if (gsl_matrix_get (vy, i, j) > 0) {
                        gsl_vector_set(b, k, (gsl_vector_get (b, k) - gsl_matrix_get (vy, i, j)*(gsl_matrix_get(To, i, j)-
                        gsl_matrix_get(To, i-1, j))/dy));
                    }
                    else {
                        gsl_vector_set(b, k, (gsl_vector_get (b, k) - gsl_matrix_get (vy, i, j)*(gsl_matrix_get(To, i+1, j)-
                        gsl_matrix_get(To, i, j))/dy));
                    }
                }
            }
        }
        // Solve system of equations Ax = b for where x is the temperature at nodes
        gsl_vector *x = gsl_vector_alloc (ny*nx);
        gsl_permutation* p = gsl_permutation_alloc (ny*nx);
        gsl_linalg_LU_decomp (mat, p, &s);
        gsl_linalg_LU_solve (mat, p, b, x);

        // Allocate values in T1
        for (int i = 0; i < ny; i++) {
            for (int j = 0; j < nx; j++) {
                int k = (j*ny) + i;
                gsl_matrix_set (T1, i, j, gsl_vector_get(x, k));
            }

        }
    gsl_matrix_free (mat);
    gsl_vector_free (b);
              
    int f = round(freq);

    if (t % f == 0 || t == 1) {    
        write_vts(output_path, freq, X, Y, t, nx, ny, T1, vx, vy);
    }

    // copy values of old time step into new
    int gsl_matrix_memcpy (gsl_matrix * To, const gsl_matrix * T1);
    }
}

void explicit_T1 (gsl_matrix* Toexp, gsl_matrix* T1exp, double dx, double dy, gsl_matrix* vx, 
                  gsl_matrix* vy, double dt, Parameters *params, int** X, int **Y) {
    
    int nx = params->nx;
    int ny = params->ny;
    double kappa = params->diff;
    int left_condition = params->left_condition;
    int right_condition = params->right_condition;
    int top_condition = params->top_condition;
    int bottom_condition = params->bottom_condition;
    double left_temp = params->temp_left;
    double right_temp = params->temp_right;
    double top_temp = params->temp_top;
    double bottom_temp = params->temp_bottom;
    double total_time = params->total_time;
    string output_path = params->output_path;
    double freq = params->output_fre;

    int tnum = round(total_time/dt); // number of time steps

    for (int t = 1; t <= tnum; t++) {
        // Allocate  matrix A in Ax = b
        gsl_matrix* mat = gsl_matrix_alloc (ny*nx, ny*nx);
        // Allocate  right side of vector , b
        gsl_vector* b   = gsl_vector_calloc (ny*nx);
       /*
        Explicit solving of 2D temperature equation:
        dT/dt=kappa*(d2T/dx2+d2T/dy2)
        Process internal grid point
        */
        for (int i = 1; i < ny - 1 ; i++) {
            for (int j = 1; j < nx - 1 ; j++) {
                // Compute advective terms
                double vxdtdx, vydtdx;
                if (gsl_matrix_get (vx, i, j) > 0) {
                    vxdtdx = gsl_matrix_get (vx, i, j)*(gsl_matrix_get(Toexp, i, j)- gsl_matrix_get(Toexp, i, j-1))/dx;
                }
                else {
                    vxdtdx = gsl_matrix_get (vx, i, j)*(gsl_matrix_get(Toexp, i, j+1)- gsl_matrix_get(Toexp, i, j))/dx;
                }
                if (gsl_matrix_get (vy, i, j) > 0) {
                    vydtdx = gsl_matrix_get (vy, i, j)*(gsl_matrix_get(Toexp, i, j)- gsl_matrix_get(Toexp, i-1, j))/dy;
                }
                else {
                    vydtdx = gsl_matrix_get (vy, i, j)*(gsl_matrix_get(Toexp, i+1, j)- gsl_matrix_get(Toexp, i, j))/dy;
                }

            // Tnew(i,j)=dt*kappa((Told(i,j-1)-2*Told(i,j)+Told(i,j+1))/dx^2
            // +(Told(i-1,j)-2*Told(i,j)+Told(i+1,j))/dy^2)+Told(i,j) -dt*(vx*dT/dx+vy*dT/dy)
            gsl_matrix_set(T1exp, i, j, dt*kappa*((gsl_matrix_get(Toexp, i, j-1) - 2*gsl_matrix_get(Toexp, i, j)
                                         + gsl_matrix_get(Toexp, i, j+1))/(dx*dx) + (gsl_matrix_get(Toexp, i-1, j)
                                         - 2*gsl_matrix_get(Toexp, i, j) + gsl_matrix_get(Toexp, i+1, j))/(dy*dy))
                                         + gsl_matrix_get(Toexp, i, j) - dt*(vydtdx + vxdtdx));
            }
        }
        // Boundary nodes
        gsl_vector* T_row = gsl_vector_calloc(nx);
        gsl_vector* T_col = gsl_vector_calloc(ny);
        switch (top_condition) {
            case 0: // Insulating
            // Upper boundary
                gsl_matrix_set_row(T1exp, 0, T_row);
            case 1: // Constant
                gsl_vector* top = gsl_vector_alloc(nx);
                gsl_vector_set_all(top, top_temp);
                gsl_matrix_set_row(T1exp, 0, top);
                gsl_vector_free (top);
            }
        switch (bottom_condition) {
            case 0: // Bottom boundary
                gsl_matrix_set_row(T1exp, ny-1, T_row);
            case 1: 
                gsl_vector* bottom = gsl_vector_alloc(nx);
                gsl_vector_set_all(bottom, bottom_temp);
                gsl_matrix_set_row(T1exp, ny-1 , bottom);
                gsl_vector_free (bottom);
            }
        switch (left_condition) {
            case 0: // Left Boundary
                gsl_matrix_set_col(T1exp, 0, T_col);
            case 1:
                gsl_vector* left = gsl_vector_alloc(ny);
                gsl_vector_set_all(left, left_temp);
                gsl_matrix_set_col(T1exp, 0, left);
                gsl_vector_free (left);
            }
        switch (right_condition) {
            case 0: // Right Boundary
                gsl_matrix_set_col(T1exp, nx-1, T_col);
            case 1: // Constant
                gsl_vector* right = gsl_vector_alloc(ny);
                gsl_vector_set_all(right, right_temp);
                gsl_matrix_set_col(T1exp, nx-1, right);
                gsl_vector_free (right);
            }
            
        gsl_vector_free (T_row);
        gsl_vector_free (T_col);
        gsl_matrix_free (mat);
        gsl_vector_free (b);
    
    int f = round(freq);

    if (t % f == 0 || t == 1) {    
        write_vts(output_path, freq, X, Y, t, nx, ny, T1exp, vx, vy);
    }
    // copy values of old time step into new
    int gsl_matrix_memcpy (gsl_matrix * Toexp, const gsl_matrix * T1exp);
    }
}

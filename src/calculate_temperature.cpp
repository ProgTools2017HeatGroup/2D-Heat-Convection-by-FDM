#include <iostream>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <math.h>
#include <cassert>
#include "calculate_temperature.h"

void implicit_T1 (gsl_matrix* To, int nx, int ny, double dx, double dy, double kappa, double dt, int left_condition,
                int right_condition, int top_condition, int bottom_condition, double left_temp, gsl_matrix* T1,
                double right_temp, double top_temp, double bottom_temp, float total_time,
                gsl_matrix* vx, gsl_matrix* vy) {

    int tnum = round(total_time/dt); // number of time steps

    enum type{
    INSULATING, CONSTANT
    };
    type boundary;

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
                        switch (boundary) {
                            case 0:
                                gsl_matrix_set (mat, k, k, 1);
                                gsl_matrix_set (mat, k, k+1, -1);
                                gsl_vector_set (b, k, 0);
                            case 1:
                                gsl_matrix_set (mat, k, k, 1);
                                gsl_vector_set (b, k, top_temp);
                            }
                        }
                    else if (i == ny - 1) {
                        switch (boundary) {
                            case 0:
                                gsl_matrix_set (mat, k, k, 1);
                                gsl_matrix_set (mat, k, k-1, -1);
                                gsl_vector_set (b, k, 0);
                            case 1:
                                gsl_matrix_set (mat, k, k, 1);
                                gsl_vector_set (b, k, bottom_temp);
                            }
                        }
                    else if (j == 1 && i > 0 && i < ny - 1){
                        switch (boundary) {
                            case 0:
                                gsl_matrix_set (mat, k, k, 1);
                                gsl_matrix_set (mat, k, k + ny, -1);
                                gsl_vector_set (b, k, 0);
                            case 1:
                                gsl_matrix_set (mat, k, k, 1);
                                gsl_vector_set (b, k, left_temp);
                            }
                        }
                    else if (j == nx - 1 && i > 0 && i < ny - 1){
                        switch (boundary) {
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
                if (gsl_matrix_get (vx, i, j) > 0){
                    gsl_vector_set(b, k, (gsl_vector_get (b, k) - gsl_matrix_get (vx, i, j)*(gsl_matrix_get(To, i, j)-
                    gsl_matrix_get(To, i, j-1))/dx));
                }
                else {
                    gsl_vector_set(b, k, (gsl_vector_get (b, k) - gsl_matrix_get (vx, i, j)*(gsl_matrix_get(To, i, j+1)-
                    gsl_matrix_get(To, i, j))/dx));
                }
                // -vy*dT/dy
                if (gsl_matrix_get (vy, i, j) > 0){
                    gsl_vector_set(b, k, (gsl_vector_get (b, k) - gsl_matrix_get (vy, i, j)*(gsl_matrix_get(To, i, j)-
                    gsl_matrix_get(To, i-1, j))/dy));
                }
                else {
                    gsl_vector_set(b, k, (gsl_vector_get (b, k) - gsl_matrix_get (vy, i, j)*(gsl_matrix_get(To, i+1, j)-
                    gsl_matrix_get(To, i, j))/dy));
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
    // copy values of old time step into new
    int gsl_matrix_memcpy (gsl_matrix * To, const gsl_matrix * T1);
    }
}

void explicit_T1 (gsl_matrix* Toexp, int nx, int ny, double dx, double dy, double kappa, double dt, int left_condition,
                int right_condition, int top_condition, int bottom_condition, double left_temp, gsl_matrix* T1exp,
                double right_temp, double top_temp, double bottom_temp, float total_time,
                gsl_matrix* vx, gsl_matrix* vy) {

    int tnum = round(total_time/dt); // number of time steps

    enum type{
    INSULATING, CONSTANT
    };

    type boundary;
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
        switch (boundary) {
            case 0: // Insulating
            // Upper boundary
                gsl_matrix_set_row(T1exp, 0, T_row);
            // Top boundary
                gsl_matrix_set_row(T1exp, ny-1, T_row);
            // Left Boundary
                gsl_matrix_set_col(T1exp, 0, T_col);
            // Right Boundary
                gsl_matrix_set_col(T1exp, nx-1, T_col);
            case 1: // Constant
                gsl_vector* top = gsl_vector_alloc(nx);
                gsl_vector_set_all(top, top_temp);
                gsl_matrix_set_row(T1exp, 0, top);

                gsl_vector* bottom = gsl_vector_alloc(nx);
                gsl_vector_set_all(bottom, bottom_temp);
                gsl_matrix_set_row(T1exp, ny-1 , bottom);

                gsl_vector* left = gsl_vector_alloc(ny);
                gsl_vector_set_all(left, left_temp);
                gsl_matrix_set_col(T1exp, 0, left);

                gsl_vector* right = gsl_vector_alloc(ny);
                gsl_vector_set_all(right, right_temp);
                gsl_matrix_set_col(T1exp, nx-1, right);

        gsl_vector_free (top);
        gsl_vector_free (bottom);
        gsl_vector_free (right);
        gsl_vector_free (left);
        gsl_vector_free (T_row);
        gsl_vector_free (T_col);
        }
    // Reassign temperature profiles for the next step
    gsl_matrix_free (mat);
    gsl_vector_free (b);

    // copy values of old time step into new
    int gsl_matrix_memcpy (gsl_matrix * Toexp, const gsl_matrix * T1exp);
    }
}

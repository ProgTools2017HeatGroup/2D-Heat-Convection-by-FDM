/**
 * @Short boundary condition program
 * @File  boundary.cpp
 *
 * Set boundary values of u,v,and p
 * According to the boundary conditions.
 * The BC flags are as follows:
 * 1: Free-slip condition (Roller)
 * 2: No-slip condition (Pin)
 *
 */

#define BC_FREE_SLIP 1
#define BC_NO_SLIP 2
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void set_boundary_conditions(int w_left, int w_right, int w_top, int w_bottom, double P, vector<vector<float> > U , vector<vector<float> > V, int nx, int ny) {
    int i,j;

    /* vertical boundaries (left and right) */
    for (j=1; j<ny+1; j++) {

        if (w_left == BC_FREE_SLIP) {
            U[0][j] = 0.0;
            V[0][j] = V[1][j];
        } else if (w_left == BC_NO_SLIP) {
            U[0][j] = 0.0;
            V[0][j] = 0.0;
        }

        if (w_right == BC_FREE_SLIP) {
            U[nx][j] = 0.0;
            V[nx+1][j] = V[1][j];
        } else if (w_right == BC_NO_SLIP) {
            U[nx+1][j] = 0.0;
            V[nx+1][j] = 0.0;
        }
    }

    /* horizontal boundaries (bottom and top) */
    for (i=1; i<nx+1; i++) {

        if (w_bottom == BC_FREE_SLIP) {
            U[i][0] = U[i][1];
            V[i][0] = 0.0;
        } else if (w_bottom == BC_NO_SLIP) {
            U[i][0] = 0.0;
            V[i][0] = 0.0;
        }

        if (w_top == BC_FREE_SLIP) {
            U[i][ny+1] = U[i][ny];
            V[i][ny] = 0.0;
        } else if (w_top == BC_NO_SLIP) {
            U[i][ny+1] = 0.0;
            V[i][ny] = 0.0;
        }
    }
}



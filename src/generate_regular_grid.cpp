/**
 * @Function generates regular rectangular grid points based on the user inputs
 * @File generate_regular_grid.cpp
 *
 * Based on user input, function generate mesh grid of the domain.
 *
 */

#include <iostream>
#include <cstdlib>
#include "generate_regular_grid.h"

using namespace std;

// Get x values at the grid
int** generate_points (int nx, int ny, double delta) {
    
    int** grid = (int**) malloc(ny * sizeof(int*));
    for (int ind = 0; ind < ny; ind++) {
        grid[ind] = (int*) malloc (nx * sizeof (int));
    }

    int x_o = 0;
    for (int i=0; i < nx; i ++) {
        for (int j=0; j < ny; j++) {
            grid[j][i] = x_o;
        }
        x_o += delta;
    }
    return grid;
}

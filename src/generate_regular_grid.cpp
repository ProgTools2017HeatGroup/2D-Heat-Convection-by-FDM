/*
 * Generates regular rectangular grid points based on the user inputs
 * March, 2017
 *
 */

#include <iostream>
#include <cstdlib>
#include "generate_regular_grid.h"

/**
 * @short generate regular grid function
 * @file  generate_regular_grid.cpp
 */

using namespace std;

// Get x values at the grid
int** generate_x_points (int x_extent, int y_extent, int nx, int ny, double dx) 
{
    int** x_grid = (int**) malloc(ny * sizeof(int*));
    for (int ind = 0; ind < ny; ind++) {
        x_grid[ind] = (int*) malloc (nx * sizeof (int));
    }

    int x_o = 0;
    for (int i=0; i < nx; i ++) {
        for (int j=0; j < ny; j++) {
            x_grid[j][i] = x_o;
        }
        x_o += dx;
    }
    return x_grid;
}

//Get Y values at the grid
int** generate_y_points (int x_extent, int y_extent, int nx, int ny, double dy) 
{
    int** y_grid = (int**) malloc (ny * sizeof(int*));
    for (int i = 0; i < ny; i++) {
        y_grid[i] = (int*) malloc (nx * sizeof (int));
    }

    int y_o = 0;
    for (int i=0; i < ny; i ++) {
        for (int j=0; j < nx; j++) {
            y_grid[i][j] = y_o;
        }
        y_o += dy;
    }
    return y_grid;
}

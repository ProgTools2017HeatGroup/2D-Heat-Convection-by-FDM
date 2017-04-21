/*
 * Calculates stable time step based on the user inputs
 * February, 2017
 *
 */

#include <iostream>
#include <math.h>
#include "stability_condition.h"

/**
 * @short stability condition calculated function
 * @file  stability_condition.cpp
 */

using namespace std;

float stable_time (double x_extent, double y_extent, int nx, int ny, float kappa,
                    gsl_matrix * vx, gsl_matrix * vy, double dx, double dy) {

    double dt;
    if (dx > dy) {
        dt =   dx*dx/(3*kappa);                         // Limitation for explicit timestep
        // Limitation for horizontal advection timestep
        if ( abs(gsl_matrix_max(vx)) !=0 && dt > (abs(dx/gsl_matrix_max(vx))) ) {
            dt = (abs(dx/gsl_matrix_max(vx)));
        }
    }
    else if (dy > dx) {
        dt =   dy*dy/(3*kappa);
        // Limitation for vertical advection timestep
        if ( abs(gsl_matrix_max(vy)) !=0 && dt > (abs(dy/gsl_matrix_max(vy))) ) {
            dt = (abs(dy/gsl_matrix_max(vy)));
        }
    }
    return (0.7*dt);
}

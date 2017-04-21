#ifndef STABILITY_CONDITION_H
#define STABILITY_CONDITION_H

#include "generate_regular_grid.h"
#include "calculate_velocity.h"

float stable_time (double x_extent, double y_extent, int nx, int ny, double kappa,
             gsl_matrix * vx, gsl_matrix * vy, double dx, double dy);

#endif

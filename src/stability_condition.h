/**
 * @Header for stable time step calculation based on input
 * @File stability_condition.h
 *
 * This file contains the prototypes of all functions used for stable time step based on user input
 *
 */


#ifndef STABILITY_CONDITION_H
#define STABILITY_CONDITION_H

#include "generate_regular_grid.h"
#include "calculate_velocity.h"

double stable_time (double kappa, gsl_matrix * vx, gsl_matrix * vy, double dx, double dy);

#endif

/**
 * @Short velocity calculation Header
 * @File calculate_velocity.h
 *
 * This file contains the prototype of velocity calculation in the domain
 *
 */

#ifndef CALCULATE_VELOCITY_H
#define CALCULATE_VELOCITY_H

#include <iostream>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <string>
#include "structs.h"

using namespace std;

void set_psi (gsl_matrix* psi, gsl_vector* x, int nx, int ny, double dx, double dy, string left_condition,
                string right_condition, string top_condition, string bottom_condition, double left_velocity,
                double right_velocity, double top_velocity, double bottom_velocity);

void set_omega (gsl_matrix* rho, gsl_vector* x, int nx, int ny, double eta, double dx, double dy);

void set_horizontal_velocity (gsl_matrix* rho,  double dx, double dy, gsl_matrix* horizontal_velocity, Parameters *params);

void set_vertical_velocity (gsl_matrix* rho,  double dx, double dy, gsl_matrix* vertical_velocity, Parameters *params);
#endif

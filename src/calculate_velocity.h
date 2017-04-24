#ifndef CALCULATE_VELOCITY_H
#define CALCULATE_VELOCITY_H

#include <iostream>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <string>

using namespace std;
// Solving Poisson equation for vorticity  d2OMEGA/dx2+d2OMEGA/dy2=gy*dRHO/dx
// Composing matrix of coefficients A()  and vector (column) of right parts b()
// Boundary conditions: OMEGA=0 ; Process all Grid points

void set_psi (gsl_matrix* psi, gsl_vector* x, int nx, int ny, double dx, double dy, string left_condition,
                string right_condition, string top_condition, string bottom_condition, double left_velocity,
                double right_velocity, double top_velocity, double bottom_velocity);

void set_omega (gsl_matrix* rho, gsl_vector* x, int nx, int ny, double eta, double dx, double dy);

void set_horizontal_velocity (gsl_matrix* rho, int nx, int ny, double eta, double dx, double dy, string left_condition,
                string right_condition, string top_condition, string bottom_condition, double left_velocity,
                double right_velocity, double top_velocity, double bottom_velocity, gsl_matrix* horizontal_velocity);

void set_vertical_velocity (gsl_matrix* rho, int nx, int ny, double eta, double dx, double dy, string left_condition,
                string right_condition, string top_condition, string bottom_condition, double left_velocity,
                double right_velocity, double top_velocity, double bottom_velocity, gsl_matrix* vertical_velocity);
#endif

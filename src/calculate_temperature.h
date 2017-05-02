/**
 * @Header for temperature calculation based on input
 * @File calculate_temperature.h
 *
 * This file contains the prototypes of all functions used for temperature calculation.
 *
 */


#ifndef CALCULATE_TEMPERATURE
#define CALCULATE_TEMPERATURE

#include "stability_condition.h"
#include "structs.h"

void implicit_T1 (gsl_matrix* To, gsl_matrix* T1, double dx, double dy, gsl_matrix* vx, gsl_matrix* vy, 
                  double dt, Parameters *params, int** X, int **Y);

void explicit_T1 (gsl_matrix* Toexp, gsl_matrix* T1exp, double dx, double dy, gsl_matrix* vx, 
                  gsl_matrix* vy, double dt, Parameters *params, int** X, int **Y);

#endif

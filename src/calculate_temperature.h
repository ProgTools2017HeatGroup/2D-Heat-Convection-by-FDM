#ifndef CALCULATE_TEMPERATURE
#define CALCULATE_TEMPERATURE

#include "stability_condition.h"
#include "structs.h"

void implicit_T1 (gsl_matrix* To, gsl_matrix* T1, double dx, double dy, gsl_matrix* vx, gsl_matrix* vy, 
                  double dt, Parameters *params);

void explicit_T1 (gsl_matrix* Toexp, gsl_matrix* T1exp, double dx, double dy, gsl_matrix* vx, 
                  gsl_matrix* vy, double dt, Parameters *params);

#endif

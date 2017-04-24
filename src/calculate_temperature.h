#ifndef CALCULATE_TEMPERATURE
#define CALCULATE_TEMPERATURE

#include "stability_condition.h"
//#include "initial_temp.h"

void implicit_T1 (gsl_matrix* To, int nx, int ny, double dx, double dy, double kappa, double dt, int left_condition,
                int right_condition, int top_condition, int bottom_condition, double left_temp, gsl_matrix* T1,
                double right_temp, double top_temp, double bottom_temp, float total_time,
                gsl_matrix* vx, gsl_matrix* vy);

void explicit_T1 (gsl_matrix* Toexp, int nx, int ny, double dx, double dy, double kappa, double dt, int left_condition,
                int right_condition, int top_condition, int bottom_condition, double left_temp, gsl_matrix* T1exp,
                double right_temp, double top_temp, double bottom_temp, float total_time,
                gsl_matrix* vx, gsl_matrix* vy);

#endif

#ifndef INITIAL_TEMP_H
#define INITIAL_TEMP_H

#include <gsl/gsl_matrix.h>
#include <iostream>

#define PI 3.14159265

// set the background value to a constant background temperature
void set_back_value (gsl_matrix* field_in, int ny_in, int nx_in, double back) ;

void set_box (gsl_matrix* field_in, double dx, double dy, double length, double height,
              double coord_x, double coord_y, double perturb, double x_extent, double y_extent) ; 

void set_disk (gsl_matrix* field_in, double dx, double dy, double radius, double coord_x,
               double coord_y, double perturb, double x_extent, double y_extent) ;

void set_gaussian (gsl_matrix* field_in,  double dx, double dy, double sigma, double coord_x,
                   double coord_y, double perturb, double x_extent, double y_extent) ;
#endif
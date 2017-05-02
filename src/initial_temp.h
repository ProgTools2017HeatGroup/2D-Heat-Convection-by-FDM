/**
 * @Header for initial_temp
 * @File initial_temp.h
 *
 * This file contains the prototypes of all functions apply the initial temperature field to domain
 *
 */


#ifndef INITIAL_TEMP_H
#define INITIAL_TEMP_H

#include <gsl/gsl_matrix.h>
#include <iostream>
#include "structs.h"

#define PI 3.14159265

// set the background value to a constant background temperature
void set_back_value (gsl_matrix* field_in, int ny_in, int nx_in, double back) ;

void set_disk (gsl_matrix* field_in, double dx, double dy, Parameters *params) ; 

void set_box (gsl_matrix* field_in, double dx, double dy, Parameters *params) ;

void set_gaussian (gsl_matrix* field_in, double dx, double dy, Parameters *params) ;
#endif

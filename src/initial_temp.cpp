/**
 * @Short initial temperature calculation program
 * @File  initial_temp.cpp
 *
 * Define various perturbations - box, disk, gaussian to start convection
 * Coord_x and coord_y define the center of the perturbation in terms of cartesian
 * Perturb represents the temperature of the perturbation and other
 * Variables corresponds to their geometries.
 *
 */


#include <math.h>
#include <cassert>
#include <string>
#include <gsl/gsl_matrix.h>
#include "initial_temp.h"
#include "structs.h"

#define PI 3.14159265


// set the background value to a constant background temperature
void set_back_value (gsl_matrix* field_in, int ny_in, int nx_in, double back) {

    for (int i = 0; i < ny_in; i++) {
        for (int j = 0; j < nx_in; j++) {
            gsl_matrix_set(field_in, i, j, back);
        }
    }

}

void set_box (gsl_matrix* field_in, double dx, double dy, Parameters *params) {

    double length = params->length;
    double height = params->width;
    double perturb = params->pert_T;
    int x_extent = params->xe;
    int y_extent = params->ye;
    int coord_x = params->xo;
    int coord_y = params->yo;

    assert(length >= 0 && height >= 0 && coord_x >= 0 && coord_y >=0 && perturb >=0);
    assert((length+coord_x)/2  < x_extent/2 && (height+coord_y)/2 < y_extent/2);

    for (int i = 0; i <= round(length/dx); i++) {
        for (int j = 0; j <= round(height/dx); j++) {
            gsl_matrix_set(field_in, round(coord_x/dx) + i , round(coord_y/dy) + j, perturb);
        }
    }

}

void set_disk (gsl_matrix* field_in, double dx, double dy, Parameters *params) {

    double radius = params->radius;
    double perturb = params->pert_T;
    int x_extent = params->xe;
    int y_extent = params->ye;
    int coord_x = params->xo;
    int coord_y = params->yo;

    assert(radius >= 0 && coord_x >= 0 && coord_y >=0 && perturb >= 0);
    assert((radius+coord_x)/2 < x_extent/2 && (radius+coord_y)/2 < y_extent/2);

    float dphi = dy/dx;
    float dr = sqrt(dx*dx + dy*dy);
    for (float phi = 0; phi <= 2*PI; phi += dphi) {
        for (float r = 0; r <= radius; r += dr) {
             int i = round((r*cos(phi) + coord_x)/dx);
             int j = round((r*sin(phi) + coord_y)/dy);
             gsl_matrix_set(field_in, i , j, perturb);
        }
    }

}

void set_gaussian (gsl_matrix* field_in, double dx, double dy, Parameters *params) {

    double sigma = params->sigma;
    double perturb = params->pert_T;
    int x_extent = params->xe;
    int y_extent = params->ye;
    int coord_x = params->xo;
    int coord_y = params->yo;

    assert(sigma >=0 && coord_x >= 0 && coord_y >= 0 && perturb >=0);
    assert((coord_x + sigma)/2 < x_extent/2 && (1/dy + coord_y < y_extent/2));

    for (int i = 0; i <= round(5*sigma/dx); i++) {
        int x = round((coord_x - 2.5*sigma)/dx) + dx;
        int y = round((exp(-(x - coord_x)*(x - coord_x)/(2*sigma*sigma)) + coord_y)/dy);
        for (int j = 0; j <= y ; j++) {
            gsl_matrix_set(field_in, x , y, perturb);
        }
    }

}

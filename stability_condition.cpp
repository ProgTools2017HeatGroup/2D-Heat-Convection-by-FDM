/*
 * Calculates stable time step based on the user inputs
 * February, 2017
 *
 */

#include <string>
#include <iostream>
#include <math.h>

using namespace std;

float mesh_scheme ;

float discrete_elements (float x_extent, float y_extent) {

    if (mesh_scheme == NULL) {
    // default meshing scheme
    mesh_scheme = 1000;}
    int points_in_x = sqrt(mesh_scheme*x_extent/(y_extent));
    int points_in_y = sqrt(mesh_scheme*y_extent/(x_extent));
    return min (points_in_x, points_in_y);
}

float stable_time_step (float horizontal_velocity, float vertical_velocity,
                        float time_step) {
    float dt =  discrete_elements(12, 13)/
                 max (horizontal_velocity, vertical_velocity) ;
    if (time_step <= dt) {
        return time_step;}
    else {
    return dt;}
    }

int main() {
    cout << "Mininum element length = "<< discrete_elements (12,10.0) << endl;
    cout << "Stable time step = " << stable_time_step (23, 45, 4) << endl;
    return 0;
}


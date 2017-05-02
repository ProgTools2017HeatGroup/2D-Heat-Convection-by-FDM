/**
 * @short boundary Header
 * @file boundary.h
 *
 * This file contains the prototype for defining the boundary types (FREE SLIP / NO SLIP)
 *
 */


#define BC_FREE_SLIP 1
#define BC_NO_SLIP 2
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


void set_boundary_conditions(int w_left, int w_right, int w_top, int w_bottom, double P, vector<vector<float> > U , vector<vector<float> > V, int nx, int ny);

#ifndef UTILITY_H_
#define UTILITY_H_

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <cstdlib>

using namespace std;

int read_float(vector<string> &str, int i, float &float_value);
int read_int(vector<string> &str, int i, int &int_value);
int read_matrix(vector<string> &str, int i, float ***matr, int *nx, int *ny);
int check_vari_float(float &vari_float, float threshold);
int check_vari_int(int &vari_int, int threshold);
void print_error();
int allocate_matrix(float ***M, int nx, int ny);
void free_matrix(float ***M, int nx);


#endif
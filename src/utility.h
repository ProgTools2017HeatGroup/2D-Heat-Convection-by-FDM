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

int read_double(vector<string> &str, int i, double &double_value);
int read_int(vector<string> &str, int i, int &int_value);
int read_string(vector<string> &str, int i, string &string_value);
int read_matrix(vector<string> &str, int i, double ***matr, int *nx, int *ny);
int check_vari_double(double &vari_double, double threshold);
int check_vari_int(int &vari_int, int threshold);
int check_vari_string(string &vari_string, string threshold);
void print_error();
int allocate_matrix(double ***M, int nx, int ny);
void free_matrix(double ***M, int nx);


#endif
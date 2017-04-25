/**
* @short   Utility Headers
* @file    utility.h
* @author  Jia Zhang
*
* This file contains the prototypes of all the functions used for i/o.
*
*/

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

// Description: These functions used for input and output 
// ------------------------------------------------------

void check_argu(int argc, char *argv[], char **infile, char **logfile);

int read_vari(vector<string> &str, int i, double &double_value);
int read_vari(vector<string> &str, int i, int &int_value);
int read_vari(vector<string> &str, int i, string &string_value);
int read_vari(vector<string> &str, int i, double ***matr, int *nx, int *ny);

int check_vari(double &vari_double, double threshold);
int check_vari(int &vari_int, int threshold);
int check_vari(string &vari_string, string threshold);

int pass_vari(vector<string> str, int i, string keyword, double *passvari);
int pass_vari(vector<string> str, int i, string keyword, int *passvari);
int pass_vari(vector<string> str, int i, string keyword, string *passvari);

void print_error();

int allocate_matrix(double ***M, int nx, int ny);
void free_matrix(double ***M, int nx);

#endif
/**
 * @short   Input and output Headers
 * @file    file_io.h
 * @author  Jia Zhang
 *
 * This file contains the prototypes all functions used for reading in and printing out.
 *
 */

#ifndef FILE_IO_H_
#define FILE_IO_H_

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <cstdlib>
#include "structs.h"

using namespace std;

// Description: These functions for reading the input and write to logfile
// -----------------------------------------------------------------------

using namespace std;

int read_infile(char* args, vector<string> &str);
int store_params(vector<string> &str, Parameters *params);
int write_logfile(char* args, Parameters *params);

#endif

/**
* @short   functions used to input and output
* @file    utility.cpp
* @author  Jia Zhang
*
* This file contains a short description of functions used for reading in and printing out.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <unistd.h> 
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
//  output values in scientific form
using std::scientific;

/**
* Author:    Jia Zhang
*
* Description: This function checks the arguments from the terminal.
* -h,-v, -i (inputfile), -o (logfile) is reasonable. Must have -i and -o options.
*
* Return     0 on success
*
* Return     EXIT_FAILURE when missing inputfile, logfile or unknown options.
*/

void check_argu(int argc, char *argv[], char **infile, char **logfile)
{
    int opt;

    while ((opt = getopt(argc, argv, "i:o:hv")) != -1)
        switch (opt)
    {
        case 'h':
            cout << "usage: " << argv[0] << " [OPTIONS][-i] INPUTFILENAME;[-o] LOGFILENAME;[-h] HELP;[-v] VERSION" << endl;
            break;
        case 'v':
            cout << argv[0] << ": Solve 2D-heat-convection using finite differences method --ver1.00" << endl;
            break;
        case 'i':
            *infile = optarg;
            cout << "Inputfile is " << *infile << endl;
            break;
        case 'o':
            *logfile = optarg;
            cout << "Logfile is " << *logfile << endl;
            break;
        case '?':
            if (optopt == 'i')
            {
                cout << "Missing inputfile option" << endl;
                exit(EXIT_FAILURE);
            }
            else if (optopt == 'o')
            {
                cout << "Missing logfile option" << endl;
                exit(EXIT_FAILURE);
            }
            else
            {
                cout << "Unknown option" << endl;
                exit(EXIT_FAILURE);
            }
        default:
            abort();
    }
    if (*logfile == NULL)
    {
        cout << "Missing logfile, please check" << endl;
        exit(EXIT_FAILURE);
    }
}

/**
* Author:    Jia Zhang
*
* Description: This function reads double variable from input to the memory and print it
* to screen.
*
* Return     0 on success
*
*/

int read_vari(vector<string> &str, int i, double &double_value)
{

    cout << str[i] << "\t=" << endl;

    char* c;
    c = const_cast<char*>(str[i + 2].c_str());
    sscanf(c, "%lf", &double_value);

    cout << scientific << double_value << endl << "\n";

    return 0;
}

/**
* Author:    Jia Zhang
*
* Description: This function reads int variable from input to the memory and print it
* to screen.
*
* Return     0 on success
*
*/

int read_vari(vector<string> &str, int i, int &int_value)
{

    cout << str[i] << "\t=" << endl;
  
    char* c;
    c = const_cast<char*>(str[i + 2].c_str());
    sscanf(c, "%d", &int_value);
    cout << scientific << int_value << endl << "\n";

    return 0;
}

/**
* Author:    Jia Zhang
*
* Description: This function reads string variable from input to the memory and print it
* to screen.
*
* Return     0 on success
*
*/

int read_vari(vector<string> &str, int i, string &string_value)
{

    cout << str[i] << "\t=" << endl;
    string_value = str[i + 2];
    cout << string_value << endl << "\n";

    return 0;
}

/**
* Author:    Jia Zhang
*
* Description: This function reads two dimensional double matrix from input to the memory 
* and print it to screen.
*
* Return     0 on success
*
*/

int read_vari(vector<string> &str, int i, double ***matr, int *nx, int *ny)
{

    cout << str[i] << "\t=" << endl;
    int j, k;
    char* c;
    for (j = 0; j < *nx; j = j + 1)
    {
        for (k = 0; k < *ny; k = k + 1)
        {
            c = const_cast<char*>(str[i + 2].c_str());
            sscanf(c, "%lf", &(*matr)[j][k]);
            cout << scientific << (*matr)[j][k] << "\t";
            i++;
        }
        cout << "\n";
    }
    cout << "\n";

    return 0;
}

/**
* Author:    Jia Zhang
*
* Description: This function check double variable from the memory with a certain 
* threshold given by user.
*
* Return     0 if variable no less than threshold
*
* Return     1 if variable less than threshold
*
*/

int check_vari(double &vari_double, double threshold)
{
    if (vari_double >= threshold)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/**
* Author:    Jia Zhang
*
* Description: This function check int variable from the memory with a certain
* threshold given by user.
*
* Return     0 if variable no less than threshold
*
* Return     1 if variable less than threshold
*
*/

int check_vari(int &vari_int, int threshold)
{
    if (vari_int >= threshold)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/**
* Author:    Jia Zhang
*
* Description: This function check string variable from the memory with a certain
* threshold given by user.
*
* Return     0 if variable equals to threshold
*
* Return     -1 or 1 if variable not equals to threshold
*
*/

int check_vari(string &vari_string, string threshold)
{
    return vari_string.compare(threshold);
}

/**
* Author:    Jia Zhang
*
* Description: This function passes double variable from the inputfile to memory if
* compatible to the keyword.
*
* Return     1 on success
*
* Return     0 on failure
*
*/

int pass_vari(vector<string> str, int i, string keyword, double *passvari)
{
    if (!str[i].compare(keyword))
    {
        read_vari(str, i, *passvari);
        return 1;
    }
    else
        return 0;
}

/**
* Author:    Jia Zhang
*
* Description: This function passes int variable from the inputfile to memory if
* compatible to the keyword.
*
* Return     1 on success
*
* Return     0 on failure
*
*/

int pass_vari(vector<string> str, int i, string keyword, int *passvari)
{
    if (!str[i].compare(keyword))
    {
        read_vari(str, i, *passvari);
        return 1;
    }
    else
        return 0;
}

/**
* Author:    Jia Zhang
*
* Description: This function passes string variable from the inputfile to memory if
* compatible to the keyword.
*
* Return     1 on success
*
* Return     0 on failure
*
*/

int pass_vari(vector<string> str, int i, string keyword, string *passvari)
{
    if (!str[i].compare(keyword))
    {
        read_vari(str, i, *passvari);
        return 1;
    }
    else
        return 0;
}

/**
* Author:    Jia Zhang
*
* Description: This function to print error message if the value of variable is unreasonable.
*
* Return     EXIT_FAILURE
*
*/

void print_error()
{
    cout << "Above is illegal input parameter, please check\n";
    exit(EXIT_FAILURE);
}

/**
* Author:    Jia Zhang
*
* Description: This function to allocate memory for 2 dimensional matrix.
*
* Return     0 on success
*
* Return     1 on failure
*
*/

int allocate_matrix(double ***M, int nx, int ny)
{
    int i;
    (*M) = (double**)malloc(sizeof(double*)*nx);
    if (*M == NULL)
        return 1;

    for (i = 0; i<nx; i++) {
        (*M)[i] = (double*)malloc(sizeof(double)*ny);
        if ((*M)[i] == NULL)
            return 1;
    }
    return 0;
}

/**
* Author:    Jia Zhang
*
* Description: This function to free memory for 2 dimensional matrix.
*
*/

void free_matrix(double ***M, int nx)
{
    int i;
    for (i = 0; i<nx; i++)
        free((*M)[i]);
    free(*M);
}
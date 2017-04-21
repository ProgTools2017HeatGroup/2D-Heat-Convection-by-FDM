#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
//  output values in scientific form
using std::scientific;

int read_double(vector<string> &str, int i, double &double_value)
{

    cout << str[i] << "\t=" << endl;

    char* c;
    c = const_cast<char*>(str[i + 2].c_str());
    sscanf(c, "f %lf", &double_value);

    cout << scientific << double_value << endl << "\n";

    return 0;
}

int read_int(vector<string> &str, int i, int &int_value)
{

    cout << str[i] << "\t=" << endl;
    char* c;
    c = const_cast<char*>(str[i + 2].c_str());
    sscanf(c, "%d", &int_value);
    cout << scientific << int_value << endl << "\n";

    return 0;
}


int read_matrix(vector<string> &str, int i, double ***matr, int *nx, int *ny)
{

    cout << str[i] << "\t=" << endl;
    int j, k;
    char* c;
    for (j = 0; j < *nx; j = j + 1)
    {
        for (k = 0; k < *ny; k = k + 1)
        {
            c = const_cast<char*>(str[i + 2].c_str());
            sscanf(c, "f %lf", &(*matr)[j][k]);
            cout << scientific << (*matr)[j][k] << "\t";
            i++;
        }
        cout << "\n";
    }
    cout << "\n";

    return 0;
}

int check_vari_double(double &vari_double, double threshold)
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

int check_vari_int(int &vari_int, int threshold)
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

void print_error()
{
    cout << "Above is illegal input parameter, please check\n";
    exit(EXIT_FAILURE);
}

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

void free_matrix(double ***M, int nx)
{
    int i;
    for (i = 0; i<nx; i++)
        free((*M)[i]);
    free(*M);
}
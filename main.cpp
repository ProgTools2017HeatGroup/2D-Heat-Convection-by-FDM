/**
 * @mainpage 2D Heat Convection Simulation Program
 *
 * This is the documentation for 2D Heat Convection Simulation Package.
 * It contains all the relevant info.
 */
#include <iostream>
#include <fstream>
#include <time.h>
#include "file_io.h"
using namespace std;
/**
 * @short Main program
 * @file  main.cpp
 * @author Arushi Saxena, Hao Lu, Jia Zhang
 * @return 0 on success
 *
 * The program aims to use finnite difference method to compute 2D heat
 * convection in a rectangular box.
 */

int main(int argc, char* argv[])
{
    clock_t start, end;
    start = clock();

    float rho, vis, diff, expa, xe, ye;
    int nx, ny; 
    float **P, **T, **Vx, **Vy;

    string str[100];

    check_infile(argc);

    read_infile(argc, argv, str);

    store_params(str, &rho, &vis, &diff, &expa, &xe, &ye, &nx, &ny, &P, &T, &Vx, &Vy);


    float time = (float)(end - start) / CLOCKS_PER_SEC;
    cout << time << endl;

    return 0;
}

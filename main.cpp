/**
 * @mainpage 2D Heat Convection Simulation Program
 *
 * This is the documentation for 2D Heat Convection Simulation Package.
 * It contains all the relevant info.
 */
#include <iostream>
#include <fstream>
#include <time.h>
/**
 * @short Main program
 * @file  main.cpp
 * @author Arushi Saxena, Hao Lu, Jia Zhang
 * @return 0 on success
 *
 * The program aims to use finnite difference method to compute 2D heat
 * convection in a rectangular box.
 */

using namespace std;

bool check_input (string inputfilename)
{
    ifstream inputfile;
    inputfile.open(inputfilename.c_str());

    if (inputfile == NULL)
    {
        cout << inputfilename << "\t not found " << endl;
        return false;
    }
    else  return true;
}

int main()
{
    clock_t start, end;
    start = clock();

    cout << "*****************************************************" << endl;
    cout << "* This package is for 2D-heat-convection simulation *" << endl;
    cout << "*****************************************************" << endl;

    if ( not check_input("readin"))
    {
        cout << "please compile readin.cpp by g++ first" << endl;
        return 0;
    }
    else if ( not check_input("log_input"))
    {
        cout << "Run ./readin inputfile ... to read the input" << endl;
        return 0;
    }

    double TIME = (double)(end - start) / CLOCKS_PER_SEC;
    cout << TIME << endl;// 5.015s

    return 0;
}

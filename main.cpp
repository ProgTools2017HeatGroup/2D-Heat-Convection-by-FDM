/**
 * @mainpage 2D Heat Convection Simulation Program
 *
 * This is the documentation for 2D Heat Convection Simulation Package.
 * It contains all the relevant info.
 */
#include <iostream>
#include <fstream>
#include <time.h>
#include <unistd.h> 
#include <cstring>
#include <vector>

#include "generate_regular_grid.h"
#include "file_io.h"
#include "utility.h"

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
//    clock_t start, end;
//    start = clock();

    double rho, vis, diff, expa;
    int  xe, ye,nx, ny;
    double **T, **Vx, **Vy;
    vector<string> str;

    int opt;
    char *infile, *logfile;

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
            infile = optarg;
//            cout << "Inputfile is " << infile << endl;
//            if (strcmp(argv[optind+2], "-o") != 0)
//            {
//                cout << "Missing logfile option" << endl;
//                exit(EXIT_FAILURE);
//            }
            break;
        case 'o':
            logfile = optarg;
            cout << "Logfile is " << logfile << endl;
            break;
        case '?':
            if (optopt == 'i')
            {
                cout << "Missing inputfile option" <<endl;
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

//    check_infile(argc);

    read_infile(infile, str);
    

    write_logfile(logfile, &rho, &vis, &diff, &expa, &xe, &ye, &nx, &ny, &T, &Vx, &Vy);

    int** X = generate_x_points (xe, ye, nx, ny);
    int** Y = generate_y_points (xe, ye, nx, ny);

//    double time = (double)(end - start) / CLOCKS_PER_SEC;
//    cout << time << endl;

    return 0;
}

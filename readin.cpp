#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
/** 
 * @short readin function
 * @file  readin.cpp
 * @param density, viscosity, diffusivity, expansion_coefficient 
 *
 *
 * This function will read in the parameters from input file and write these values to a log file, and 
 * print them out to the screen in scientific form at the meantime. The usage is: ./readin parameters.in
 */

using namespace std;
//  output values in scientific form
using std::scientific;

int print_value (string str[100], string nam, int i, float &value, ofstream &file)
{
    char* c;

    nam = str[i];
    file << nam << "\t=" << endl;
    cout << nam << "\t=" << endl;

    c = const_cast<char*>(str[i + 2].c_str());
    sscanf(c, "%e", &value);
    file << scientific << value << endl << "\n";
    cout << scientific << value << endl << "\n";

    return 0;
}

int print_matrix (string str[100], string nam, int i, float(&matrix)[3][5], ofstream &file)
{
    int j, l;
    char* c;

    nam = str[i];
    file << nam << "\t=" << endl;
    cout << nam << "\t=" << endl;

    for (j = 0; j < 3; j = j + 1)
    {
        for (l = 0; l < 5; l = l + 1)
        {
            c = const_cast<char*>(str[i + 2].c_str());
            sscanf(c, "%e", &matrix[j][l]);
            file << scientific << matrix[j][l] << "\t";
            cout << scientific << matrix[j][l] << "\t";
            i++;
        }
        file << "\n";
        cout << "\n";
    }
    file << "\n";
    cout << "\n";

    return 0;
}

int main(int argc, char* argv[])
{
    string s,nam;
    int line_length = 100;
    string str[line_length];
    float rho, v, k, a, xe, ye;
    float P[3][5], T[3][5], Vx[3][5], Vy[3][5];
    int i;

    if (argc < 2)
    { 
        cout << "Missing inputfile, please check\n";
        return EXIT_FAILURE;
     }

//  open the input file and read the parameters in string format    
    ifstream infile;
    infile.open(argv[1]);
    i = 0;
    while (infile >> s)
    { 
        str[i] = s;
        i++;
     }
    infile.close();

//  open the log file, and wtite the input values in float format      
    ofstream logfile;
    logfile.open("log_input");
    i = 0;
    while (str[i] != "")
    {
        if (str[i] == "density")                 print_value(str,nam,i,rho,logfile);
        if (str[i] == "viscosity")               print_value(str,nam,i,v,logfile);
        if (str[i] == "diffusivity")             print_value(str,nam,i,k,logfile);
        if (str[i] == "expansion_coefficient")   print_value(str,nam,i,a,logfile);
        if (str[i] == "x_extend")                print_value(str,nam,i,xe,logfile);
        if (str[i] == "y_extend")                print_value(str,nam,i,ye,logfile);

        if (str[i] == "Pressure")                print_matrix(str,nam,i,P,logfile);
        if (str[i] == "Temperature")             print_matrix(str,nam,i,T,logfile);
        if (str[i] == "Velocity_X")              print_matrix(str,nam,i,Vx,logfile);
        if (str[i] == "Velocity_Y")              print_matrix(str,nam,i,Vy,logfile);

        i++;
    }
    logfile.close();

    return 0;
}

/*
 * Reads parameter file for 2-D mantle convection in box and generates log file
 * February, 2017
 *
 */

#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;

//string store_parameter_values (string &parameter_name, string &parameter_value) {
int main(){

    string return_value;
    ifstream inputfile ("params.in");
    ofstream outputfile;
    string line;

    outputfile.open("log.txt");

    while (getline(inputfile, line)) {
        // find position where equal to sign is
        int position = line.find('=');
        string parameter_name = line.substr(0,position-1);
        string parameter_value = line.substr(position+1);

        outputfile << parameter_name << '=' << parameter_value << endl ;
        float var = atof(parameter_value.c_str());
        cout << var << endl;
        }

    // Closing files
    inputfile.close();
    outputfile.close();

}


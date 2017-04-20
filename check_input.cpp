/*
 Function for checking input variables
 This function is plugged in readin.cpp function
 If threshold value for variable is not met, exit and output error message
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
using namespace std;

int check_input(string str, float variable, float threshold)
{
    if (variable >= threshold) {
        cout << "The value of " << str << " is acceptable.\n" << endl;
        return 0;
    }

    else {
        cout << "The value of " << str << " is not acceptable, please check.\n" << endl;
        exit(EXIT_FAILURE);
    }
}




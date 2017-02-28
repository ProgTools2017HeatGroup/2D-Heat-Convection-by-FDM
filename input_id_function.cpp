#include <iostream>

using namespace std;

//Function to identify input


int Input_id ()

{
    
    int Density = 1000;
    
    if (Density < 0) {
 
    cont << "Density Must Be Positive" <<endl;
    
    exit (1);

    }


int Viscosity = 1000;

    if (Viscosity < 0) {

    cont << "Viscosity Must Be Positive" <<endl;

    exit (1);

    }

    return 0;

}

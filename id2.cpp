#include <iostream>

using namespace std;

int ID (int Density, int Viscosity)

{
	if (Density <= 0)
		
		throw Density;

	if (Viscosity <= 0)

		throw Viscosity;

	return 0;

}

int main (int argc, char const *argv[])

{
	int Density, Viscosity;

	cout << "Density (kg/m3):";
	
	cin  >> Density;

	cout << "Viscosity (cp):";

	cin  >>Viscosity;

	try

	{
		ID (Density, Viscosity);
	}

	catch (int)

	{
		cout << "Input value must be positive." << endl;
	}

	return 0;
}


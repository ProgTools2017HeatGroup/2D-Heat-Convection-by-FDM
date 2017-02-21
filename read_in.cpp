#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

    ifstream inFile;
    inFile.open("filename.txt");

    //Check For Error
    if (inFile.fail()) {
        cerr << "Error Opening File" << endl;
        exit(1);

    }

    int x, y;

    inFile >> x >> y;
    //Reading First And Second Number In filename.txt
    cout << "Num 1: " << x << endl;
    cout << "Num 2: " << y << endl;

    return 0;

}





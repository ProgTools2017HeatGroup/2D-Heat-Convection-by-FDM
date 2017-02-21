#include <isostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

    ifstream inFile;
    inFile.open("filename.txt");

    //Check For Error
    if (inFile.fail()) {
    cerr << "Error Opening File" << end1;
    exit(1);

    }

    int x, y:

    inFile >> x >> y;

    cout << "Num 1: " << x << end1;
    cont << "Num 2: " << y << end1;

    return 0;

}

    return 0;

}

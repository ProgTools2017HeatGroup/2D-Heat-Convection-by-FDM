/*
 * Generates regular rectangular grid points based on the user inputs
 * March, 2017
 *
 */

#include <iostream>
#include <vector>

using namespace std;

 int points_in_x = 2;
 int points_in_y = 4;
 int x_extent = 4;
 int y_extent = 12;
vector<float> x_grid(points_in_x);
vector<float> y_grid(points_in_y);

main () {

    float dx = x_extent/points_in_x;
    float dy = y_extent/points_in_y;

    int x_o , y_o = 0;

    for (int i=0; i < points_in_x; i ++) {
        x_grid[i] = x_o;
        cout << "Grid points along X: " << x_grid[i] << " " << endl;
        x_o += dx;
    }

    for (int j=0; j < points_in_y; j++) {
        y_grid[j] = y_o;
        cout << "Grid points along Y: " << y_grid[j] << " " << endl;
        y_o += dy;
    }

    return 0;
}

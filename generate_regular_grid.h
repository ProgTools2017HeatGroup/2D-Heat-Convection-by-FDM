#ifndef REGULAR_GRID
#define REGULAR_GRID

double get_dx (int x_extent, int nx) {
    return x_extent/nx;
}

double get_dy (int y_extent, int ny) {
    return y_extent/ny;
}

int** generate_x_points (int x_extent, int y_extent, int nx, int ny);

int** generate_y_points (int x_extent, int y_extent, int nx, int ny);

#endif

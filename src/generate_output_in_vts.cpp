#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <gsl/gsl_matrix.h>

using namespace std;

// Simple function to enable name output files by string name
std::string to_string(int i) {
    
    std::stringstream ss;
    ss << i;
    return ss.str();
}

void write_vts(string dirname, int** X, int** Y, double t,
              int nx, int ny, gsl_matrix* T, gsl_matrix* Vx, gsl_matrix* Vy) { 

    // Create output filename based on time step
    string fname = "fields." + to_string(t) + ".vts";

    cout << "Writing output file for current time step" << fname << endl;

    // Create output directory for outfile.
    mkdir(dirname.c_str(),S_IRWXU);
    string fullpath = "./" + dirname + "/" + fname;

    // Create output file.
    ofstream fout(fullpath.c_str(), ios::out);

    // Write begining part of .vts file.
    // WholeExtent is adjustable based on user input file (domain size)
    fout << "<\?xml version=\"1.0\"\?>" << endl;
    fout << "<VTKFile type=\"StructuredGrid\" version=\"1.0\" byte_order=\"LittleEndian\">" << endl;
    fout << "<StructuredGrid WholeExtent=\"0 " << nx - 1<< " 0 " << ny - 1 << " 0 0\">" << endl;
    fout << "<Piece Extent=\"0 " << nx - 1 << " 0 " << ny - 1 << " 0 0\">" << endl;
    fout << "<CellData></CellData>" << endl << "<Points>" << endl;
    fout << "<DataArray type=\"Float64\" NumberOfComponents=\"3\" format=\"ascii\">" << endl;

    // Start writing coordinates info
    // For .vts file, x coordinate increase first, then y coordinate, thus outer loop for y, inner loop for x
    for (int i = 0; i < ny; i++) {          
        for (int j = 0; j < nx; j++) {          
        fout << X[i][j] << " " << Y [j][i] << " 0" << endl;
        }
    }

    // Another part of title, Name= VelocityField shows the data type. In paraview, this name will show up
    // represant this series of data sets
    fout << "</DataArray>" << endl << "</Points>" << endl;
    fout << "<PointData Vectors=\"VelocityField\">" << endl;
    fout << "<DataArray type=\"Float64\" Name=\"VelocityField\" format=\"ascii\" NumberOfComponents=\"3\">" << endl;

    // Start writing velocity field for each nodel point based on output velocity matrix
    // Format in "Vx Vy Vz" for first point, then change line, same drill.
    // 2D case, z components stay 0
    for (int i = 0; i < ny; i++) {          
        for (int j = 0; j < nx; j++) {  
            fout << gsl_matrix_get(Vx,i,j) << " " << gsl_matrix_get(Vy,i,j) << " 0" << endl;
        }
    }

    // Another part of title, Name= Temperature shows the data type.
    fout << "</DataArray>" << endl;
    fout << "<DataArray type=\"Float64\" Name=\"Temperature\" format=\"ascii\" NumberOfComponents=\"1\">" << endl;


    // Start writing temperature distribution for each time step.
    // Same way to count each nodel point, x increase first, then y.
    // But this time for .vts file, should write in one colume, starts with first point (leastx, leasty, least z)
    for (int i = 0; i < ny; i++) {          
        for (int j = 0; j < nx; j++) {            
            fout << gsl_matrix_get(T,i,j) << endl;
        }
    }

    // Write bottom of file.
    // In .vts file, each <****> should be end with </****>
    fout << "</DataArray>" << endl << "</PointData>" << endl << "</Piece>" << endl;
    fout << "</StructuredGrid>" << endl << "</VTKFile>" << endl;

    cout << "Finish writing output file for current time step" << fname << endl;

    // Finish writing, close file
    fout.close();

}
     















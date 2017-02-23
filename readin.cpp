#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;
//  output values in scientific form
using std::scientific;
	
int print_value(string str[100],int i,float &value,ofstream &file);
int print_matrix(string str[100],int i,float (&matrix)[3][5],ofstream &file);
		
//  purpose: read in the parameters from input file and write these values to a log file
//  usage: ./readin parameters.in logfile 
int main(int argc, char* argv[])
{
    
    string s;
    int line_length = 100;
    string str[line_length];
    float rho, v, k, a;
    float P[3][5], T[3][5], Vx[3][5], Vy[3][5];
    int i;
        
    
    if(argc < 3)
    { 
        cout << "Missing inputfile or logfile, please check\n";
        return EXIT_FAILURE;
     }
    
    
//  open the input file and read the parameters in string format    
    ifstream infile;
    infile.open(argv[1]);

    i = 0;
    while( infile >> s )
    { 
        str[i] = s;
        i++;
     }
    
    infile.close();
    
      
//  open the log file, and wtite the input values in float format      
    ofstream logfile;
    logfile.open(argv[2]);
      
    i = 0;
    while(str[i] != "")
    {
        if(str[i] == "rho=") print_value(str,i,rho,logfile);
        if(str[i] == "v=")   print_value(str,i,v,logfile);
        if(str[i] == "k=")   print_value(str,i,k,logfile);
        if(str[i] == "a=")   print_value(str,i,a,logfile);
         	
        if(str[i] == "P=")   print_matrix(str,i,P,logfile);
        if(str[i] == "T=")   print_matrix(str,i,T,logfile);
        if(str[i] == "Vx=")  print_matrix(str,i,Vx,logfile);
        if(str[i] == "Vy=")  print_matrix(str,i,Vy,logfile);
         	
        i++;
    }
    
    logfile.close();

    return 0;
}



int print_value(string str[100],int i, float &value, ofstream &file) 	
{
    char* c;
             
    c = const_cast<char*>(str[i+1].c_str());
    sscanf(c,"%e", &value);
    file << scientific << value << endl;
    file << "\n";
    cout << scientific << value << endl;
                             
    return 0;
}
         

int print_matrix(string str[100],int i, float (&matrix)[3][5], ofstream &file)
{
    int j,l;
    char* c;
         	   
    for(j = 0; j < 3; j = j+1)
    {
        for(l =0; l < 5; l = l+1)
        {
            c = const_cast<char*>(str[i+1].c_str());        	                    
            sscanf(c,"%e", &matrix[j][l]);
            file << scientific << matrix[j][l] << "\t";
            cout <<  scientific << matrix[j][l] << endl;
            i++;
         }
        file << "\n"; 
     }
    file << "\n";
             
    return 0;
}





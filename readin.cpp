#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;
//  output values in scientific form
using std::scientific;
		
//  purpose: read in the parameters from input file and write these values to a log file
//  usage: ./readin parameters.in logfile 
int main(int argc, char* argv[])
{
    
    string s;
    int line_length = 100;
    string str[line_length];
    float rou, v, k, a;
    float P[3][5], T[3][5], Vx[3][5], Vy[3][5];
    int i,j,l;
    char* c;
    
    
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
         if(str[i] == "rou=")
         {
             c = const_cast<char*>(str[i+1].c_str());
             sscanf(c,"%e", &rou);
             logfile << scientific << rou << endl;
             logfile << "\n";
             i++;
         }
         else if(str[i] == "v=")
         {
             c = const_cast<char*>(str[i+1].c_str());
             sscanf(c,"%e", &v);
             logfile << scientific << v << endl;
             logfile << "\n";
             i++;
         }    
         else if(str[i] == "k=")
         {
             c = const_cast<char*>(str[i+1].c_str());        	
             sscanf(c,"%e", &k);
             logfile << scientific << k << endl;
             logfile << "\n";
             i++;
         }
         else if(str[i] == "a=")
         {
             c = const_cast<char*>(str[i+1].c_str());        	
             sscanf(c,"%e", &a);
             logfile << scientific << a << endl;
             logfile << "\n";
             i++;
         }    
         else if(str[i] == "P=")
         {
             for(j = 0; j < 3; j = j+1)
             {
                for(l =0; l < 5; l = l+1)
                {
                    c = const_cast<char*>(str[i+1].c_str());        	                    
                    sscanf(c,"%e", &P[j][l]);
                    logfile << scientific << P[j][l] << "\t";
                    i++;
                 }
                logfile << "\n"; 
              }
             logfile << "\n";
         }
         else if(str[i] == "T=")
         {
             for(j = 0; j < 3; j = j+1)
             {
                for(l =0; l < 5; l = l+1)
                {
                    c = const_cast<char*>(str[i+1].c_str());        	                    
                    sscanf(c,"%e", &T[j][l]);
                    logfile << scientific << T[j][l] << "\t";
                    i++;
                 }
                logfile << "\n";
              }
             logfile << "\n";
         }    
         else if(str[i] == "Vx=")
         {
             for(j = 0; j < 3; j = j+1)
             {
                for(l =0; l < 5; l = l+1)
                {
                    c = const_cast<char*>(str[i+1].c_str());        	                    
                    sscanf(c,"%e", &Vx[j][l]);
                    logfile << scientific << Vx[j][l] << "\t";
                    i++;
                 }
                logfile << "\n";
              }
             logfile << "\n";
         }
         else if(str[i] == "Vy=")
         {
             for(j = 0; j < 3; j = j+1)
             {
                for(l =0; l < 5; l = l+1)
                {
                    c = const_cast<char*>(str[i+1].c_str());        	                    
                    sscanf(c,"%e", &Vy[j][l]);
                    logfile << scientific << Vy[j][l] << "\t";
                    i++;
                 }
                logfile << "\n";
              } 
             logfile << "\n";           
         }
         i++;   
    }
    logfile.close();

    return 0;
}







#include <stdio.h>
#include <time.h>
 
int main()
{
    clock_t start,end; // typedef long clock_t
    start = clock();
    long i= 1000000000L; while(i--){}
    end = clock();
 
    //#define CLOCKS_PER_SEC ((clock_t)1000)
    double duration =(double)(end-start)/CLOCKS_PER_SEC;
    cout << duration << endl; // 4.015s
 
    return 0;
}

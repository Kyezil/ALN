#include <iostream>
#include <valarray>
#include <iostream>
#include <ctime>
#include "LU.hh"
using namespace std ;

double gettime_hp();

int main()
{
    enum { N = 5*1024*1024 };
    LU a(N);
    int i,j;
    for(  j=0 ; j<8 ; ++j )
    {
        for(  i=0 ; i<N ; ++i )
            a(i,j)=rand();

        double* a1 = &a[0], *b1 = &b[0], *c1 = &c[0] ;
        double dtime=gettime_hp();
        for(  i=0 ; i<N ; ++i ) c1[i] = a1[i] * b1[i] ;
        dtime=gettime_hp()-dtime;
        cout << "double operator* " << dtime << " ms\n" ;

        dtime=gettime_hp();
        c = a*b ;
        dtime=gettime_hp()-dtime;
        cout << "valarray operator* " << dtime << " ms\n" ;

        dtime=gettime_hp();
        for(  i=0 ; i<N ; ++i ) c[i] = a[i] * b[i] ;
        dtime=gettime_hp()-dtime;
        cout << "valarray[i] operator* " << dtime<< " ms\n" ;

        cout << "------------------------------------------------------\n" ;
    }
}

double gettime_hp()
{
    struct timespec timestamp;

    clock_gettime(CLOCK_REALTIME, &timestamp);
    return timestamp.tv_sec * 1000.0 + timestamp.tv_nsec * 1.0e-6;
}

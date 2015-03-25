#include <iostream>
#include <valarray>
#include <iostream>
#include <ctime>
#include "LU.hh"
using namespace std ;

double gettime_hp();

int main()
{
    int N;
    while (cin >> N) {
    LU a(N);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            a(i,j) = rand();
        }
    }
    double dtime=gettime_hp();
    a.factorize();
    dtime=gettime_hp()-dtime;
    cout << "Needed time " << dtime << " ms\n" ;
    }
}
double gettime_hp()
{
    struct timespec timestamp;

    clock_gettime(CLOCK_REALTIME, &timestamp);
    return timestamp.tv_sec * 1000.0 + timestamp.tv_nsec * 1.0e-6;
}

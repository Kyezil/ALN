#include <iostream>
#include <cmath>
using namespace std;

struct Pair {
    double SN;
    int N;
}; 

Pair sum_N(int r, double eps) {
    //PRE: r odd r > 1
    //POST: <SN*, N*> SN sum using N iterations : er < eps
    Pair res;
    res.SN = 0;
    res.N = 1;
    double SN_i;
    do {
        SN_i = 1./pow(res.N++,r);
        res.SN += SN_i;
    }   
    while (SN_i/res.SN >= eps);
    return res;
}

void print(int r, const Pair& p) {
    cout << r << ' ' << p.N << ' ' << p.SN << ' ' << p.SN/pow(M_PI,r) << endl;
}

int main() {
    cout.setf(ios::fixed);
    cout.precision(20);
    int r;
    while (cin >> r) {
        print(r, sum_N(r,1.e-14));
    }
}

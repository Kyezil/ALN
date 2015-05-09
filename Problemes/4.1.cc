#include <iostream>
#include <cmath>
using namespace std;

double i_exp_mcL(double x, double coef, int i, int N) {
    // coef = 1/i!  0 <= i <= N
    if (i == N) return coef;
    else return coef + x*i_exp_mcL(x, coef/(i+1), i+1, N);
}

double exp_mcL(double x, int N) {
    // PRE N >= 0
    // POST e^x usant Horner amb polinomi de McLaurin de grau N
    return i_exp_mcL(x, 1, 0, N);
}

int main() {
    cout << exp_mcL(0.5,10) << endl;
}

#include <iostream>
#include <cmath>
using namespace std;

template<typename T>
T i_exp_mcL(T x, T coef, int i, int N) {
    // coef = 1/i!  0 <= i <= N
    if (i == N) return coef;
    return coef + x*i_exp_mcL(x, coef/(i+1), i+1, N);
}

template<typename T>
T exp_mcL(T x, int N) {
    // PRE N >= 0
    // POST e^x usant Horner amb polinomi de McLaurin de grau N
    return i_exp_mcL<T>(x, 1, 0, N);
}

template<typename T>
void taula(int x) {
    T expC = exp(x);
    printf("exp(%d)\t%f\n", x, expC);
    T expMC = exp_mcL<T>(x,10);
    T err = fabs(expMC-expC);
    printf("p10(%d)\t%f\t%f\t%f\n", x, expMC, err, err/fabs(expMC));

    expMC = 1/exp_mcL<T>(-x,10);
    err = fabs(expMC-expC);
    printf("q10(%d)\t%f\t%f\t%f\n", x, expMC, err, err/fabs(expMC));
}

void mostra_taules(int x) {
    cout << "Precisió simple\n";
    taula<float>(x);
    cout << "\nPrecisió doble\n";
    taula<double>(x);
    cout << '\n';
}

int main() {
    // aproximació de e^(-2)
    mostra_taules(-2);
    mostra_taules(-7);
}

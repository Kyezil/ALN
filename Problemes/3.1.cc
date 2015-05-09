#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int main() {
    float E = 1 - 1.0/M_E; // E0
    for (int i = 1; i <= 12; ++i) {
        E = 1 - i*E;
    }
    printf("E12 = %f\n", E);
    /* E12 = -4.310974
     * No pot ser negatiu perquè:
     *  x^n >= 0 en [0,1]
     *  e^(x-1) > 0 sempre
     *  1^n = 1 > 0 = 0^n
     * Els errors en E0 s'acumulen amb factor n!
     */
    E = 0; //E20 ~= 0
    for (int i = 19; i > 12; --i) {
        E = (1-E)/i;
    }
    printf("E12 = %f\n", E);

    vector<float> e1(21), e2(21), e3(21);
    e1[0] = 1 - 1.0/M_E;
    for (int i = 1; i <= 20; ++i) e1[i] = 1 - i*e1[i-1];
    e2[20] = 0;
    // calcul amb taylor de e^x d'ordre 10
    // es calcula la integral directament
    for (int i = 0; i <= 20; ++i) {
        double en = 1.0/(i+1); // 1r sumand
        double fact = 1;
        for (int k = 1; k <= 10; ++k) {
            fact /= k;
            en += fact/(i+k+1);
        }
        e3[i] = en/M_E;
    }

    for (int i = 19; i >= 0; --i) e2[i] = (1-e2[i+1])/(i+1);
    for (int i = 0; i <= 20; ++i) printf("%d\t%f\t%f\t%f\n",i,e1[i],e2[i], e3[i]);
}

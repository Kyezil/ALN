#include <iostream>
#include <vector>
#include <cmath>
#include <cfenv>
#define eps 1e-9
using namespace std;

double fraccont(double x, vector<long> &an, int &n) {
    /* Pre:  x a real number, n >= 0 */
    /* Post: pn[i]/qn[i] = k-èsima reducció de la fracció continua de x */
    fesetround(FE_DOWNWARD); // floor rounding
    // first elements for recursion
    long a = lrint(x);
    long p0 = 1, q0 = 0;
    long p1 = a, q1 = 1;
    an.push_back(a);
    n = 0;
    double x_c = x;
    double err = fabs(x_c - p1/q1);
    printf("%ld\t: %ld/%ld\n",a,p1,q1);
    while (err > eps) {
        ++n;
        x = 1.0/(x-a);
        a = lrint(x);
        an.push_back(a);
        swap(p0,p1);
        p1 += a*p0; //p1 = p1*a + p0
        swap(q0,q1);
        q1 += a*q0; //q1 = q1*a + q0
        err = fabs(x_c - double(p1)/q1);
        printf("%ld\t: %ld/%ld\n", a,p1,q1);
    }
    x = x_c;
    //printf("%d %ld %ld %e\n", n, p1, q1, err);
    return err;
}

void print_frac(vector<long> &an) {
    cout << '[' << an[0];
    if (an.size() > 1) cout << ';' << an[1];
    for (int i = 2; i < an.size(); ++i) {
        cout << ',' << an[i];
    }
    cout << "]\n";
}

int main() {
    cout.setf(ios::scientific);
    int n;
    double x;
    cin >> x;
    vector<long int> an;
    double err = fraccont(x,an,n);
    print_frac(an);
    printf("eps = %e\nn = %d\n", err, n);
}

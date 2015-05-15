#include <iostream>
#include <cmath>
#include "mat.hh"
using namespace std;

void LDL(const Mat& A, Mat& L, Mat& d) {
    int n = A.rows();
    L.diag() = 1;
    for (int k = 1; k <= n; ++k) {
        double sum = 0;
        for (int r = 1; r < k; ++r) sum += L(k,r)*L(k,r)*d(r);
        d(k)= A(k,k) - sum;
        for (int i = k+1; i <= n; ++i) {
            sum = 0;
            for (int r = 1; r < k; ++r) sum += L(i,r)*d(r)*L(r,r);
            L(i,k) = (A(i,k) - sum)/d(k);
        }
    }
}

int main() {
    Mat A(3,3), L(3,3), d(3,1);
    cin >> A;
    LDL(A,L,d);
    cout << "Matriu L\n" << fixed << L << '\n'
         << "Matriu D\n" << fixed << d << endl;
}

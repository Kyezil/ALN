#include <iostream>
#include <cmath>
#include "mat.hh"
using namespace std;

Mat cholesky(const Mat& A) {
    int n = A.rows();
    Mat L(n,n);
    for (int j = 1; j <= n; ++j) {
        double sum = 0;
        for (int k = 1; k < j; ++k) sum += L(j,k)*L(j,k);
        L(j,j) = sqrt(A(j,j) - sum);
        for (int i = j+1; i <= n; ++i) {
            sum = 0;
            for (int k = 1; k < j; ++k) sum += L(i,k)*L(j,k);
            L(i,j) = (A(i,j) - sum)/L(j,j);
        }
    }
    return L;
}

int main() {
    Mat A(3,3);
    cin >> A;
    cout << cholesky(A);
}

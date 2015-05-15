#include <iostream>
#include <cmath>
#include "mat.hh"
#include "vec.cc"
using namespace std;
#define eps 1.e-9

void jacobi(const Mat& A, const Mat& b, Mat& x0, int maxit) {
    Mat x = x0;
    for (int k = 1; k <= maxit; ++k) {
        for (int i = 1; i <= x0.rows(); ++i) {
            double sum = 0;
            int j = 1;
            while (j < i) {
                sum += A(i,j)*x0(j);
                ++j;
            }
            ++j; //salta la i
            while (j <= x0.rows()) {
                sum += A(i,j)*x0(j);
                ++j;
            }
            x(i) = (b(i) - sum)/(A(i,i));
        }
        x0 = x;
        if (Mat::norm2(static_cast<valarray<double> >(x.col(1)) -
                   static_cast<valarray<double> >(x0.col(1))) < eps) break;
    }
}

int main() {
//    cout.precision(20);
    Mat A(3,3), b (3,1);
    cin >> A >> b;
    Mat x (3,1);
    jacobi(A,b,x,100);
    cout << "solució\n" << x << endl;
}

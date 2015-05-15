#include <iostream>
#include <cmath>
#include "mat.hh"
#include "vec.cc"
using namespace std;

void QR(Mat& Q, Mat& R) {
    int m = Q.rows();
    int n = Q.cols();
    for (int k = 1; k <= n; ++k) {
        R(k,k) = Mat::norm2(Q.col(k));
        for (int i = 1; i <= m; ++i) Q(i,k) /= R(k,k); //normalitza
        for (int s = k+1; s <= n; ++s) {
            R(k,s) = dot(Q.col(k), Q.col(s)); //projecció
            for (int i = 1; i <= m; ++i) Q(i,s) -= R(k,s)*Q(i,k); //ortogonal
        }
    }
}

void solveQR(const Mat& Q, const Mat& R, Mat& x, const Mat& b) {
    Mat::bwsb(R, x, Mat::transpose(Q)*b);
}

int main() {
//    cout.precision(20);
    Mat A(3,3);
    cin >> A;
    Mat Q = A;
    Mat R(3,3);
    QR(Q,R);
    cout << "Matriu Q\n";
    Mat::printOctave(Q,cout);
    cout << "\nMatriu R\n";
    Mat::printOctave(R, cout);

    Mat b (3,1);
    cin >> b;
    Mat x (3,1);
    solveQR(Q,R,x,b);
    cout << "solució\n" << x << endl;
}

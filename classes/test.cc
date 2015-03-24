#include "LU.hh"
#include "Matrix.hh"
#include <iostream>
using namespace std;
int main() {
    unsigned n;
    cout << "Enter dimension of Matrix:" << endl;
    cin >> n;
    
    LU mat(n);
    mat.read();
    mat.print_L();
    cout << std::endl;
    mat.print_U();
    cout << std::endl;
    mat.print_P();
}

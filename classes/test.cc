#include "LU.hh"
#include <iostream>
using namespace std;
int main() {
    int n;
    cout << "Enter dimension of Matrix:" << endl;
    cin >> n;

    LU mat(n);
    mat.read('p');
    mat.print_L();
    cout << std::endl;
    mat.print_U();
    cout << std::endl;
    mat.print_P();
}

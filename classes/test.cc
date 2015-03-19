#include "LU.hh"
#include <iostream>

int main() {
    LU mat(3);
    mat.read();
    mat.print_L();
    std::cout << std::endl;
    mat.print_U();
}

/**
 * @file generator.cc
 * @brief Generate matrix_A.dat and vector_b.dat for ALN
 * @author Louis Clergue <louisclergue@gmail.com>
 * @version 1.0 01/04/15

Compilation:
g++ -std=c++11 generator.cc -o generator.exe

Use :
./generator.exe             generate with default parameters
./generator.exe N           generate matrix NxN and vector Nx1 with default range
./generator.exe N min max   same as above but element range = [min,max]

N        : unsigned int >= 0        default = 10
min, max : double (min <= max)      default = -100, 100

Note: (min == max) will result in all elements equals => rang(matrix) = 1
*/
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <random>
#include <cassert>

/**
 * @brief Generate a Matrix NxN and a vector Nx1 with element in [minim, maxim]
 * @param N the dimensions of vector/matrix
 * @param minim lower bound (inclusive) for elements
 * @param maxim upper bound (inclusive) for elements
 * @pre minim <= maxim, write permission
 * @post generate matriu_A.dat and vector_b.dat
 *
 * Output Matrix -> matriu_A.dat in format:
 * N
 * A11 A12 ... A1N
 * A21 A22 ... A2N
 * ... ... ... ...
 * AN1 AN2 ... ANN
 *
 * Output Vector -> vector_b.dat in format:
 * N
 * b1
 * b2
 * ...
 * bN
*/
void genMatVec(unsigned N, double minim, double maxim);

int main(int argc, char *argv[]) {
    int N = 10;
    double minim = -100, maxim = 100;

    if (argc > 2 and argc != 4) {
        std::cout << "Incorrect input for " << argv[0] << '\n'
            << "Correct syntax needs : \n"
            << "  - no parameters -> N = 10, min = -100, max = 100\n"
            << "  - 1 parameters N\n"
            << "  - 3 parameters N min max\n"
            << "(unsigned) N = # rows/cols of matrix\n"
            << "(double) min/max = minim/maxim value of elements"
            << std::endl;
    }
    else {
        if (argc >= 2) N = atoi(argv[1]);
        if (argc == 4) minim = atof(argv[2]), maxim = atof(argv[3]);
        assert(N >= 0);
        genMatVec(N, minim, maxim);
    }
}

void genMatVec(unsigned N, double minim, double maxim) {
    assert(minim <= maxim);

    std::cout << "Generating matrix/vector with N=" << N
        << ", min=" << minim << ", max=" << maxim << '.' <<  std::endl;

    std::uniform_real_distribution<double> unif(minim, maxim);
    std::default_random_engine re;
    auto rd = [&] () {return unif(re);};

    std::ofstream out;
    srand(time(NULL));

    out.open("vector_b.dat");
    if (not out.is_open()) throw std::runtime_error("Can't output to vector_b.dat");
    out << N << '\n';
    for (unsigned i = 0; i < N; ++i) out << rd() << '\n';
    out.close();

    out.open("matriu_A.dat");
    if (not out.is_open()) throw std::runtime_error("Can't output to matriu_A.dat");
    out << N << '\n';
    for (unsigned i = 0; i < N; ++i) {
        for (unsigned j = 0; j < N; ++j)
            out << rd() << ' ';
        out << '\n';
    }
    out.close();
    std::cout << "Successfully generated" << std::endl;

}

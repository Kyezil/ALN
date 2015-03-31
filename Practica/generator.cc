#include <fstream>
#include <iostream>
#include <stdexcept>
#include <random>
#include <cassert>

int main(int argc, char *argv[]) {
    unsigned N = 10;
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
        if (argc >= 2) N = atof(argv[1]);
        if (argc == 4) minim = atof(argv[2]), maxim = atof(argv[3]);
        assert(N > 0);
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
}



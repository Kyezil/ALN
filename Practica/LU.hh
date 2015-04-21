#ifndef LU_HH
#define LU_HH
#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <cmath>
#include "Matrix.hh"
class LU {
    typedef unsigned short US;
    typedef std::vector<double> VD;
    typedef std::vector<US> VUS;
    
    public:
        Matrix A, Ai, Ac;
        US N;
        VUS P;
        bool signP;
        VD b;
        double detA;

        LU(US dim);

        void pivot(const US i);
        void decompose();
        void forward_substitution(VD& x, VD& b); //Lx = b
        void backward_substitution(VD& x, VD& b); //Ux = b

        void inverse();

        void det();
};
#endif

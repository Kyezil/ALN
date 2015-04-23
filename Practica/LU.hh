#ifndef LU_HH
#define LU_HH
#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <cmath>
#include "Matrix.hh"
class LU {
    public:
        typedef unsigned short US;
        typedef std::vector<double> VD;
        typedef std::vector<US> VUS;

        Matrix A, Ai, Ac;
        US N;
        VUS P;
        VUS Pt;

        bool signP;
        VD b;
        double detA;

        LU(US dim);

        void pivot(const US i);
        void decompose();
        void forward_substitution(VD& x, const VD& b); //Lx = b
        void backward_substitution(VD& x, const VD& b); //Ux = b
        
        void inverse();
        void gen_Pt();

        void det();

        static void print_L(const Matrix& A);
        static void print_U(const Matrix& A);
        void read_b(std::ifstream& in);
        static void print_vec(std::ofstream& out, const VD& x);
};
#endif

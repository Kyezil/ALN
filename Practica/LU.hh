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

        struct normError {
            double err1, err2, errInf;
        };

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
        void forward_substitution(VD& x, const VD& b) const; //Lx = b
        void backward_substitution(VD& x, const VD& b) const; //Ux = b

        void inverse();
        void gen_Pt();
        void permP(Matrix& A) const;

        void det();
        double getEl(const US i, const US j) const;
        double normInf() const;

        normError normsAx_b(const VD& x) const;

        static void print_L(const Matrix& A);
        static void print_U(const Matrix& A);
        void read_b(std::ifstream& in);
        static void print_vec(std::ofstream& out, const VD& x);

};
#endif

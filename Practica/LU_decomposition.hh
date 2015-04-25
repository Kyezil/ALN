#ifndef LU_HH
#define LU_HH
#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <cmath>
#include "Matrix.hh"
class LU_decomposition {
    private:
        typedef unsigned short US;
        typedef std::vector<double> VD;
        typedef std::vector<US> VUS;

        US N;
        Matrix LU;

        VUS P;
        VUS Pt;

        bool signP;

        void pivot(const US i);
        void decompose();
        void forward_substitution(VD& x, const VD& b) const; //Lx = b
        void backward_substitution(VD& x, const VD& b) const; //Ux = b
    public:
        LU_decomposition(const Matrix& A, std::ofstream & matLU);

        void inverseA(Matrix& Ai);
        void solveAx_b(const VD& b, VD& x);

        double detA();
        double getLU(const US i, const US j) const;

        double normInfPA_LU(const Matrix& A) const;

        static void print_L(const Matrix& A);
        static void print_U(const Matrix& A);
};
#endif

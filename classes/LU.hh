/* Class LU */
#ifndef LU_HH
#define LU_HH
#include "Matrix.hh"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <utility>

class LU {
    typedef std::pair<unsigned, unsigned> Pos;
    private:
        Matrix mat;
        void descompose(Pos (*f)(Matrix&, const unsigned));
        //apply Gauss reduction
        static const unsigned OUT_DIGITS = 5;
    public:
       
        static Pos partial_pivoting(Matrix& mat, const unsigned i);
        //max element of row
        static Pos partial_scaled_pivoting(Matrix& mat, const unsigned i);
        //relative max element of column 
        static Pos total_pivoting(Matrix& mat, const unsigned i);
        //max element
        LU();
        //\pre true
        //\post default constructor matrix 0x0

        LU(const unsigned n);
        //\pre  true
        //\post creates a matrix NxN

        void read();
        //\pre  initialized NxN matrix and NxN doubles at input
        //\post read doubles and perform descomposition LU

        void print_L() const;
        //\pre  matrix has been descomposed
        //\post prints L matrix

        void print_U() const;
        //\pre matrix has been descomposed
        //\post prints U matrix

        void print_P() const;
        //\pre initialized matrix
        //\post prints P matrix
};
#endif

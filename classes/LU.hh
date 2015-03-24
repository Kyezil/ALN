/* Class LU */
#ifndef LU_HH
#define LU_HH
#include "SQ_Matrix.hh"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <utility>

class LU {
    private:
        SQ_Matrix mat; 

        void factorize();
        //apply Gauss reduction
        void partial_pivoting(const unsigned i);
        //max element of row
        void partial_scaled_pivoting(const unsigned i);
        //relative max element of column 
        void total_pivoting(const unsigned i);
        //max element
    public: 
        static const unsigned OUT_DIGITS = 5;

        LU(const unsigned n);
        //\pre  true
        //\post creates a matrix NxN
        
        //operator for initialization of matrix
        double& operator()(unsigned i, unsigned j);

        void read();
        //\pre  initialized NxN matrix and NxN doubles at input
        //\post read doubles

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

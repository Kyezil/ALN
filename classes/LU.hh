/* Class LU */
#ifndef LU_HH
#define LU_HH
#include "Matrix.hh"
class LU : public Matrix {
    private:
        void descompose(void (LU::*pivot)(const unsigned i));
        //apply Gauss reduction
        void partial_pivoting(const unsigned i);
        //max element of row
        void partial_scaled_pivoting(const unsigned i);
        //relative max element of column 
        void total_pivoting(const unsigned i);
        //max element
    public:
        LU();
        //\pre true
        //\post default constructor matrix 0x0

        LU(const unsigned n);
        //\pre  true
        //\post creates a matrix NxN

        void read(char c);
        //\pre  initialized NxN matrix and NxN doubles at input
        // @param c: t use total_pivoting
        //           s use partial_scaled_pivoting
        //           p use partial_pivoting
        //           else do not pivot
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

/* Class SQ_Matrix */
#ifndef SQ_MATRIX_HH
#define SQ_MATRIX_HH
#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>
class SQ_Matrix {
    typedef std::vector<double> VD;
    typedef std::vector<VD> VVD;
    typedef std::vector<int> VI;
    private:
        VVD mat;
    protected:
        VI rows_;
        const static unsigned OUT_DIGITS = 5;
    public:
        const unsigned N;
        const VI& rows;;

        SQ_Matrix();

        SQ_Matrix(const unsigned n);
        //\pre  true
        //\post creates a matrix NxN

        SQ_Matrix(const SQ_Matrix& mat);
        //\pre true
        //\post copy constructor

        ~SQ_Matrix();

        double& operator()(const unsigned i, const unsigned j);
        double operator()(const unsigned i, const unsigned j) const;
        // define operator for access
        void swap_row(const unsigned i1, const unsigned i2);
        //\pre  0 <= i1, i2 < N  i1 != i2
        //\post permut row i1 <-> row i2
        //\cost constant

        void read();
        //\pre  initialized MxN matrix and MxN doubles at input
        //\post read doubles

        void print(std::string name) const;
        //\pre true
        //\post print content of matrix with name as header
};
#endif

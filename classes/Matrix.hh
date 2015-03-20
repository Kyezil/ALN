/* Class Matrix */
#ifndef MATRIX_HH
#define MATRIX_HH
class Matrix {
    private:
        double ** mat;
        int *rows, *cols;
        int M, N;
        const static unsigned OUT_DIGITS = 5;
    public:
        Matrix();
        //\pre true
        //\post default constructor matrix 0x0

        Matrix(const unsigned m, const unsigned n);
        //\pre  true
        //\post creates a matrix MxN
        
        Matrix(const unsigned n);
        //\pre  true
        //\post creates a matrix NxN

        ~Matrix();

        double& operator()(const unsigned i, const unsigned j);
        double operator()(const unsigned i, const unsigned j) const;
        // define operator for access

        void perm_row(const unsigned i1, const unsigned i2);
        //\pre  0 <= i1, i2 < N  i1 != i2
        //\post permut row i1 <-> row i2
        //\cost constant

        void perm_col(const unsigned j1, const unsigned j2);
        //\pre  0 <= j1, j2 < N  j1 != j2
        //\post permut col j1 <-> col j2
        //\cost constant
        
        void read();
        //\pre  initialized MxN matrix and MxN doubles at input
        //\post read doubles
        
        void print() const;
        //\pre true
        //\post print content of matrix
};
#endif

/* Class LU */
#ifndef LU_HH
#define LU_HH
class LU {
    private:
        double ** mat;
        int *rows;
        int dim;
        void descompose();
        const static unsigned OUT_DIG = 5;
    public:
        LU();
        //\pre true
        //\post default constructor matrix 0x0

        LU(const unsigned n);
        //\pre  true
        //\post creates a matrix NxN

        ~LU();

        void read();
        //\pre  initialized NxN matrix and NxN doubles at input
        //\post read doubles and perform descomposition LU
        
        void print() const;
        //\pre true
        //\post print content of matrix

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

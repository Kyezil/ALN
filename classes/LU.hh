/* Class LU */
#ifndef LU_HH
#define LU_HH
class LU {
    private:
        double ** mat;
        unsigned dim;
        void descompose();
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
        void print_L() const;
        //\pre  matrix has been descomposed
        //\post prints L matrix

        void print_U() const;
        //\pre matrix has been descomposed
        //\post prints U matrix
};
#endif

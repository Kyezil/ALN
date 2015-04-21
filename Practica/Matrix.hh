#ifndef MATRIX_HH
#define MATRIX_HH
#include <vector>
#include <fstream>
#include <stdexcept>
class Matrix {
    private:
        std::vector<std::vector<double> > mat;
    public:
        unsigned short dim;

        Matrix();
        Matrix(const Matrix& m);
        void set_dim(const unsigned short N);

        inline const double operator()(const int i, const int j) const {
            return mat[i][j];
        }
        inline double& operator()(const int i, const int j) {
            return mat[i][j];
        }

        void swap_row(const unsigned short r, const unsigned short s);

        void read(std::ifstream& in);
        void write(std::ofstream& out) const;
};
#endif

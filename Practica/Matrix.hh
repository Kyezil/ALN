#ifndef MATRIX_HH
#define MATRIX_HH
#include <vector>
#include <fstream>
#include <stdexcept>
class Matrix {
    typedef unsigned short US;
    private:
        std::vector<std::vector<double> > mat;
    public:
        unsigned short dim;

        Matrix();
        Matrix(const Matrix& m);
        void set_dim(const US N);

        inline const double operator()(const US i, const US j) const {
            return mat[i][j];
        }
        inline double& operator()(const US i, const US j) {
            return mat[i][j];
        }
        inline void push(const US i, double el) {
            mat[i].push_back(el);
        }
        void swap_row(const US r, const US s);

        void read(std::ifstream& in);
        void write(std::ofstream& out) const;
        void write_rev(std::ofstream& out) const;
};
#endif
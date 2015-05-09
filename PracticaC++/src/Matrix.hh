#ifndef MATRIX_HH
#define MATRIX_HH
#include <vector>
#include <fstream>
#include <stdexcept>
#include <cmath>
#include <functional>
class Matrix {
    private:
        typedef unsigned short US;
        typedef std::vector<double> VD;
        typedef std::vector<VD> VVD;
        US dim;
        VVD mat;
    public:
        Matrix();
        Matrix(const Matrix& m);
        Matrix(const US N, const bool pushable = false);
        Matrix(const US N, std::ifstream& in);

        inline double operator()(const US i, const US j) const {
            return mat[i][j];
        }
        inline double& operator()(const US i, const US j) {
            return mat[i][j];
        }
        inline VD& operator()(const US i) {
            return mat[i];
        }

        inline void push(const US i, double el) {
            mat[i].push_back(el);
        }

        inline void swap_row(const US r, const US s) {
            mat[r].swap(mat[s]);
        }

        US get_dim() const;

        static double norm1(const Matrix &m);
        static double normInf(const Matrix &m);

        void write(std::ofstream& out) const;
        void write_t(std::ofstream& out) const;
};
#endif

#include "Matrix.hh"

Matrix::Matrix() : dim(0) {};
Matrix::Matrix(const Matrix& m): mat(m.mat), dim(m.dim) {};

const double& Matrix::operator()(const int i, const int j) const {
    return mat[i][j];
};
double Matrix::operator()(int i, int j) {
    return mat[i][j];
};

void Matrix::swap_row(const unsigned short r, const unsigned short s) {
    mat[r].swap(mat[s]);
};

void Matrix::read(std::ifstream& in) {
    if (in.is_open()) {
        in >> dim;
        mat.resize(dim);
        // llegeix matriu A
        for (unsigned i = 0; i < dim; ++i) {
            mat[i].reserve(dim);
            for (unsigned j = 0; j < dim; ++j) {
                double x;
                in >> x;
                mat[i].push_back(x);
            }
        }
        in.close();
    }
    else throw std::runtime_error("Matrix:read - Error file not open");
};

void Matrix::write(std::ofstream& out) const {
    if (out.is_open()) {
        for (unsigned i = 0; i < dim; ++i) {
            out << mat[i][0];
            for (unsigned j = 1; j < dim; ++j) out << ' ' << mat[i][j];
            out << '\n';
        }
    }
    else throw std::runtime_error("Matrix:write - Error file not open");
};

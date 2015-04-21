#include "Matrix.hh"

Matrix::Matrix() : dim(0) {};
Matrix::Matrix(const Matrix& m): mat(m.mat), dim(m.dim) {};

void Matrix::set_dim(const unsigned short N) {
    mat.resize(N);
    for (int i = 0; i < N; ++i) mat[i].reserve(N);
    dim = N;
}

void Matrix::swap_row(const unsigned short r, const unsigned short s) {
    mat[r].swap(mat[s]);
};

void Matrix::read(std::ifstream& in) {
    if (in.is_open()) {
        for (unsigned i = 0; i < dim; ++i) {
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

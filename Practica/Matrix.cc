#include "Matrix.hh"

Matrix::Matrix() : dim(0) {}
Matrix::Matrix(const Matrix& m): mat(m.mat), dim(m.dim) {}

void Matrix::set_dim(const unsigned short N) {
    mat.resize(N);
    for (int i = 0; i < N; ++i) mat[i].reserve(N);
    dim = N;
}

void Matrix::swap_row(const unsigned short r, const unsigned short s) {
    mat[r].swap(mat[s]);
}

double Matrix::norm1(const Matrix &m) {
    //maximum absolut column sum
    double norm = 0;
    for (unsigned j = 0; j < m.dim; ++j) {
        double sum_j = 0;
        for (unsigned i = 0; i < m.dim; ++i) sum_j += std::fabs(m(i,j));
        if (sum_j > norm) norm = sum_j;
    }
    return norm;
}

double Matrix::normInf(const Matrix &m) {
    //maximum absolut row sum
    double norm = 0;
    for (unsigned i = 0; i < m.dim; ++i) {
        double sum_i = 0;
        for (unsigned j = 0; j < m.dim; ++j) sum_i += std::fabs(m(i,j));
        if (sum_i > norm) norm = sum_i;
    }
    return norm;
}

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
}

void Matrix::write(std::ofstream& out) const {
    if (out.is_open()) {
        for (unsigned i = 0; i < dim; ++i) {
            out << mat[i][0];
            for (unsigned j = 1; j < dim; ++j) out << ' ' << mat[i][j];
            out << '\n';
        }
    }
    else throw std::runtime_error("Matrix:write - Error file not open");
}

void Matrix::write_rev(std::ofstream& out) const {
    if (out.is_open()) {
        for (unsigned j = 0; j < dim; ++j) {
            out << mat[0][j];
            for (unsigned i = 1; i < dim; ++i) out << ' ' << mat[i][j];
            out << '\n';
        }
    }
    else throw std::runtime_error("Matrix:write_rev - Error file not open");
}

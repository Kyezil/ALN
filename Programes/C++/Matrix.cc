#include "Matrix.hh"
Matrix::Matrix() : dim(0) {}
Matrix::Matrix(const Matrix& m): dim(m.dim), mat(m.mat) {}
Matrix::Matrix(const US N, const bool pushable) : dim(N) {
    mat.resize(N);
    std::function<void(US i)> op;
    if (pushable) op = [this, N](US i) {this->mat[i].reserve(N);};
    else op = [this, N](US i) {this->mat[i].resize(N);};
    for (US i = 0; i < N; ++i) op(i);
}

Matrix::Matrix(const US N, std::ifstream& in) : Matrix(N,true) {
    for (US i = 0; i < dim; ++i) {
        for (US j = 0; j < dim; ++j) {
            double x;
            in >> x;
            mat[i].push_back(x);
        }
    }
}

Matrix::US Matrix::get_dim() const {
    return dim;
}
double Matrix::norm1(const Matrix &m) {
    double norm = 0;
    for (US j = 0; j < m.dim; ++j) {
        double sum_j = 0;
        for (US i = 0; i < m.dim; ++i) sum_j += std::fabs(m(i,j));
        if (sum_j > norm) norm = sum_j;
    }
    return norm;
}

double Matrix::normInf(const Matrix &m) {
    double norm = 0;
    for (US i = 0; i < m.dim; ++i) {
        double sum_i = 0;
        for (US j = 0; j < m.dim; ++j) sum_i += std::fabs(m(i,j));
        if (sum_i > norm) norm = sum_i;
    }
    return norm;
}

void Matrix::write(std::ofstream& out) const {
    for (US i = 0; i < dim; ++i) {
        out << mat[i][0];
        for (US j = 1; j < dim; ++j) out << ' ' << mat[i][j];
        out << '\n';
    }
}

void Matrix::write_t(std::ofstream& out) const {
    if (out.is_open()) {
        for (US j = 0; j < dim; ++j) {
            out << mat[0][j];
            for (US i = 1; i < dim; ++i) out << ' ' << mat[i][j];
            out << '\n';
        }
    }
    else throw std::runtime_error("Matrix:write_rev - Error file not open");
}

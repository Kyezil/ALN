#include "Matrix.hh"
#include <cmath>
#include <iostream>
#include <iomanip>
Matrix::Matrix() {
    M = N = 0;
}

Matrix::Matrix(const unsigned m, const unsigned n) {
    M = m, N = n;
    mat = new double*[N];
    rows = new int[N];
    cols = new int[M];
    for (int i = 0; i < N; ++i) {
        mat[i] = new double[M];
        rows[i] = i;
    }
    for (int i = 0; i < M; ++i) cols[i] = i;
}
Matrix::Matrix(const unsigned n) { 
    M = N = n;
    mat = new double*[N];
    rows = new int[N];
    cols = new int[N];
    for (int i = 0; i < N; ++i) {
        mat[i] = new double[M];
        rows[i] = i;
        cols[i] = i;
    }
}
Matrix::~Matrix() {
    for (int i = 0; i < N; ++i) delete [] mat[i];
    delete [] mat;
    delete [] rows;
    delete [] cols;
}


void Matrix::perm_row(const unsigned i1, const unsigned i2) {
    std::swap(rows[i1], rows[i2]);
}

void Matrix::perm_col(const unsigned j1, const unsigned j2) {
    std::swap(cols[j1], cols[j2]);
}

double& Matrix::operator()(const unsigned i, const unsigned j) {
    return mat[rows[i]][cols[j]];
}
double Matrix::operator()(const unsigned i, const unsigned j) const {
    return mat[rows[i]][cols[j]];
}

void Matrix::read() {
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            std::cin >> mat[i][j];
    std::cerr << "Have read the matrix!" << std::endl;
}

void Matrix::print() const {
    std::cout.precision(OUT_DIGITS);
    std::cout.setf(std::ios::fixed);
    std::cout << "Matrix" << std::endl;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << std::right << std::setw(10) << mat[i][j];
        }
        std::cout << std::endl;
    }
}

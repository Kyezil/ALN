#include "SQ_Matrix.hh"

SQ_Matrix::SQ_Matrix() : N(0), rows(rows_){}

SQ_Matrix::SQ_Matrix(const unsigned n) : N(n), rows(rows_){
    mat.resize(N);
    rows_.resize(N);
    for (int i = 0; i < N; ++i) {
        mat[i].resize(N);
        rows_[i] = i;
    }
}

SQ_Matrix::SQ_Matrix(const SQ_Matrix& mat2) : N(mat2.N), rows(rows_){
    mat = mat2.mat;
    rows_ = mat2.rows_;
}

SQ_Matrix::~SQ_Matrix() {
}

void SQ_Matrix::swap_row(const unsigned i1, const unsigned i2) {
    std::swap(rows_[i1], rows_[i2]);
    std::swap(mat[i1], mat[i2]);
//    std::clog << "Swapped rows " << i1 << " and " << i2 << std::endl;
}

double& SQ_Matrix::operator()(const unsigned i, const unsigned j) {
    return mat[i][j];
}
double SQ_Matrix::operator()(const unsigned i, const unsigned j) const {
    return mat[i][j];
}

void SQ_Matrix::read() {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            std::cin >> mat[i][j];
    std::clog << "Have read the matrix!" << std::endl;
}

void SQ_Matrix::print(std::string name = "SQ_Matrix") const {
    std::cout.precision(OUT_DIGITS);
    std::cout.setf(std::ios::fixed);
    std::cout << name << std::endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << std::right << std::setw(10) << mat[i][j];
        }
        std::cout << std::endl;
    }
}

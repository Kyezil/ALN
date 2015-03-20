#include "LU.hh"
#include <cmath>
#include <iostream>
#include <iomanip>
LU::LU() : Matrix(){}

LU::LU(const unsigned n) : Matrix(n) {}

void LU::partial_scaled_pivoting(unsigned i) {
        //Permut row, scaled partial pivoting
        double max_pivot = 0;
        unsigned pivot_row = i;
        for (int j = i; j < N; ++j) {
            //get max element of row j
            double max = std::abs((*this)(j,i));
            for (int k = j+1; k < M; ++k)
                if (std::abs((*this)(j,k)) > max) max = std::abs((*this)(j,k));
            max = std::abs((*this)(j,i))/max;
            if (max > max_pivot) {
                max_pivot = max;
                pivot_row = j;
            }
        }
        //Swap rows
        if (pivot_row != i) {
            std::cerr << "Perform swap of rows: " << i << " and " << pivot_row << std::endl;
            perm_row(i,pivot_row);
        }
}

void LU::total_pivoting(unsigned i) {
        //Permut row and column, total pivoting
        double max_pivot = 0;
        unsigned pivot_row = i, pivot_col = i;
        for (int j = i; j < N; ++j) {
            for (int k = j; k < M; ++k) {
                if (std::abs((*this)(j,k)) > max_pivot) {
                    max_pivot = std::abs((*this)(j,k));
                    pivot_row = j;
                    pivot_col = k;
                }
            }
        }
        //SWAP
        if (pivot_row != i) {
            std::cerr << "Perform swap of rows: " << i << " and " << pivot_col << std::endl;
            perm_row(i,pivot_row);
        }
        if (pivot_col != i) {
            std::cerr << "Perform swap of cols: " << i << " and " << pivot_col << std::endl;
            perm_col(i,pivot_col);
        }
}

void LU::descompose(void (LU::*pivot)(const unsigned)){
    //For each row
for (int i = 0; i < N; ++i) {
    //Gauss reduction
    if(pivot) (this->*pivot)(i);
    for (int j = i+1; j < N; ++j) {
        double Mij = (*this)(j,i) / (*this)(i,i);
        (*this)(j,i) = Mij;
        for (int k = i+1; k < M; ++k) (*this)(j,k) -= Mij*(*this)(i,k);
    }
}
}
void LU::read(char c) {
    Matrix::read();
    void (LU::*pivot)(const unsigned) = NULL;
    if (c == 'p') pivot = &LU::partial_scaled_pivoting;
    else if (c == 't') pivot = &LU::total_pivoting;
    descompose(pivot);
}

void LU::print_L() const {
std::cout.precision(OUT_DIGITS);
std::cout.setf(std::ios::fixed);
std::cout << "Matrix L" << std::endl;
for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
        std::cout << std::right << std::setw(10);
        if (i < j) std::cout << 0;
        else if (i == j) std::cout << 1;
        else std::cout << (*this)(i,j);
    }
    std::cout << std::endl;
}
}

void LU::print_U() const {
std::cout.precision(OUT_DIGITS);
std::cout.setf(std::ios::fixed);
std::cout << "Matrix U" << std::endl;
for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
        std::cout << std::right << std::setw(10);
        if (i > j) std::cout << 0;
        else std::cout << (*this)(i,j);
    }
    std::cout << std::endl;
}
}
void LU::print_P() const {
std::cout << "Matrix P" << std::endl;
for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
        if (j != 0) std::cout << ' ';
        if (j == rows[i]) std::cout << 1;
        else std::cout << 0;
    }
    std::cout << std::endl;
}
}

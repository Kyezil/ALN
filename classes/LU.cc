#include "LU.hh"
#include <cmath>
#include <iostream>
#include <iomanip>
LU::LU() {}

LU::LU(const unsigned n) {
    dim = n;
    mat = new double*[dim];
    rows = new int[dim];
    for (int i = 0; i < dim; ++i) {
        mat[i] = new double[dim];
        rows[i] = i;
    }
}
LU::~LU() {
    for (int i = 0; i < dim; ++i) delete [] mat[i];
    delete [] mat;
    delete [] rows;
}

void LU::descompose(){
    //For each row
    for (int i = 0; i < dim; ++i) {
        //Permut row, scaled partial pivoting
        double max_pivot = 0;
        unsigned pivot_row = i;
        for (int j = i; j < dim; ++j) {
            //get max element of row j
            double max = std::abs(mat[j][i]);
            for (int k = j+1; k < dim; ++k)
                if (std::abs(mat[j][k]) > max) max = std::abs(mat[j][k]);
            max = std::abs(mat[j][i])/max;
            if (max > max_pivot) {
                max_pivot = max;
                pivot_row = j;
            }
        }
        //Swap rows
        if (pivot_row != i) {
            std::cerr << "Perform swap of rows: " << i << " and " << pivot_row << std::endl;
            std::swap(mat[i], mat[pivot_row]);
            std::swap(rows[i],rows[pivot_row]);
        }
        //Gauss reduction
        for (int j = i+1; j < dim; ++j) {
            double Mij = mat[j][i] / mat[i][i];
            mat[j][i] = Mij;
            for (int k = i+1; k < dim; ++k) mat[j][k] -= Mij*mat[i][k];
        }
    }
}
void LU::read() {
    for (int i = 0; i < dim; ++i)
        for (int j = 0; j < dim; ++j)
            std::cin >> mat[i][j];
    std::cerr << "Have read the matrix!" << std::endl;
    descompose();
}

void LU::print() const {
    std::cout.precision(OUT_DIG);
    std::cout.setf(std::ios::fixed);
    std::cout << "Matrix" << std::endl;
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            std::cout << std::right << std::setw(10) << mat[i][j];
        }
        std::cout << std::endl;
    }
}

void LU::print_L() const {
    std::cout.precision(OUT_DIG);
    std::cout.setf(std::ios::fixed);
    std::cout << "Matrix L" << std::endl;
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            std::cout << std::right << std::setw(10);
            if (i < j) std::cout << 0;
            else if (i == j) std::cout << 1;
            else std::cout << mat[i][j];
        }
        std::cout << std::endl;
    }
}

void LU::print_U() const {
    std::cout.precision(OUT_DIG);
    std::cout.setf(std::ios::fixed);
    std::cout << "Matrix U" << std::endl;
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            std::cout << std::right << std::setw(10);
            if (i > j) std::cout << 0;
            else std::cout << mat[i][j];
        }
        std::cout << std::endl;
    }
}
void LU::print_P() const {
    std::cout << "Matrix P" << std::endl;
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            if (j != 0) std::cout << ' ';
            if (j == rows[i]) std::cout << 1;
            else std::cout << 0;
        }
        std::cout << std::endl;
    }
}

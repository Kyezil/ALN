#include "LU.hh"
#include <cmath>
#include <iostream>
LU::LU() {
    dim = 0;
}

LU::LU(const unsigned n) {
    dim = n;
    mat = new double*[dim];
    for (int i = 0; i < dim; ++i) mat[i] = new double[dim];
}
LU::~LU() {
    for (int i = 0; i < dim; ++i) delete [] mat[i];
    delete [] mat;
}
void LU::descompose(){
    //For each row
    for (int i = 0; i < dim; ++i) {
        //Permut row, scaled partial pivoting
        double max_pivot = 0;
        unsigned pivot_row = i;
        for (int j = i; j < dim; ++j) {
            //get max element of row j
            double max = std::abs(mat[i][j]);
            for (int k = j+1; k < dim; ++k) {
                if (std::abs(mat[j][k]) > max) {
                    max = std::abs(mat[j][k]);
                }
            }
            max = mat[j][i]/max;
            if (max > max_pivot) {
                max_pivot = max;
                pivot_row = j;
            }
        }
        //Swap rows
        if (pivot_row != i) {
            std::cerr << "Perform swap of rows: " << i << " and " << pivot_row << std::endl;
            double * tmp;
            tmp = mat[i];
            mat[i] = mat[pivot_row];
            mat[pivot_row] = tmp;
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
    std::cout << "Matrix" << std::endl;
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            if (j != 0) std::cout << ' ';
            std::cout << mat[i][j];
        }
        std::cout << std::endl;
    }
}

void LU::print_L() const {
    std::cout << "Matrix L" << std::endl;
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            if (j != 0) std::cout << ' ';
            if (i < j) std::cout << 0;
            else if (i == j) std::cout << 1;
            else std::cout << mat[i][j];
        }
        std::cout << std::endl;
    }
}

void LU::print_U() const {
    std::cout << "Matrix U" << std::endl;
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            if (j != 0) std::cout << ' ';
            if (i > j) std::cout << 0;
            else std::cout << mat[i][j];
        }
        std::cout << std::endl;
    }
}

#include "LU.hh"
LU::LU(US dim) : signP(false), N(dim) {
    A.set_dim(dim);
    Ai.set_dim(dim);
    Ac.set_dim(dim);
    P.reserve(dim);
    for (int i = 0; i < dim; ++i) P.push_back(i);
};

void LU::pivot(const US i) {
    unsigned pivot_row = i;
    double pivot = 0;
    for (unsigned j = i; j < N; ++j) {
        // maxim de la fila j
        double max = std::fabs(A(i,j));
        for (unsigned k = j+1; k < N; ++k)
            if(std::fabs(A(j,k)) > max) max = std::fabs(A(j,k));
        max = std::fabs(A(j,i))/max;
        if (max > pivot) pivot = max, pivot_row = j;
    }
    if (pivot_row != i) {
        A.swap_row(i, pivot_row);
        std::swap(P[i], P[pivot_row]);
        std::clog << "    Files " << i << " <-> " << pivot_row << std::endl;
        signP = not signP;
    }
};

void LU::decompose() {
    for (unsigned i = 0; i < N; ++i) { //per a cada fila
        pivot(i);
        for (unsigned j = i+1; j < N; ++j) {
            double Mij = A(j,i)/A(i,i);
            A(j,i) = Mij;
            for (unsigned k = i+1; k < N; ++k) A(j,k) -= Mij*A(i,k);
        }
    }
};

void LU::forward_substitution(VD& x, VD& b) {}; //Lx = b

void LU::backward_substitution(VD& x, VD& b) {}; //Ux = b

void LU::inverse() {};

void LU::det() {
    detA = (signP)? -1 : 1;
    for (unsigned i = 0; i < N; ++i) detA *= A(i,i);
};

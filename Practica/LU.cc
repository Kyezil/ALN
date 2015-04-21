#include "LU.hh"
LU::LU(US dim) : signP(false), N(dim) {
    A.set_dim(dim);
    Ac.set_dim(dim);
    P.reserve(dim);
    for (int i = 0; i < dim; ++i) P.push_back(i);
}

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
}

void LU::decompose() {
    for (unsigned i = 0; i < N; ++i) { //per a cada fila
        pivot(i);
        for (unsigned j = i+1; j < N; ++j) {
            double Mij = A(j,i)/A(i,i);
            A(j,i) = Mij;
            for (unsigned k = i+1; k < N; ++k) A(j,k) -= Mij*A(i,k);
        }
    }
}

void LU::forward_substitution(VD& x, VD& b) {} //Lx = b

void LU::backward_substitution(VD& x, VD& b) {} //Ux = b

void LU::inverse() {
    Ai.set_dim(N);
    // Solve AX = I  <=>  PAX = P  <=>  LUX = P <=> {LY=P , UX=Y}
    std::clog << "    - LY = P" << std::endl;
    for (US k = 0; k < N; ++k) {
        US j = P[k]; //column j has k zeros
        US i = 0;
        while (i < k) Ai.push(j,0), ++i;
        Ai.push(j,1), ++i;
        while (i < N) {
            double y = 0;
            for (US s = k; s < i; ++s) y += A(i,s)*Ai(j,s);
            Ai.push(j,-y);
            ++i;
        }
    }

    std::clog << "    - UX = Y" << std::endl;
    for (unsigned j = 0; j < N; ++j) {
        int k = N-1;
        Ai(j,k) /= A(k,k);
        while (--k >= 0) {
            double x = 0;
            for (unsigned s = k+1; s < N; ++s) x += A(k,s)*Ai(j,s);
            Ai(j,k) = (Ai(j,k) - x)/A(k,k);
        }
        
    }
}

void LU::det() {
    detA = (signP)? -1 : 1;
    for (unsigned i = 0; i < N; ++i) detA *= A(i,i);
}

void LU::print_L(const Matrix& A) {
    for (US i = 0; i < A.dim; ++i) {
        for (US j = 0; j < A.dim; ++j) {
            if (j < i) std::cout << A(i,j);
            else if (j == i) std::cout << 1;
            else std::cout << 0;
            std::cout << ' ';
        }
        std::cout << '\n';
    }
    std::cout << std::endl;
}
void LU::print_U(const Matrix& A) {
    for (US i = 0; i < A.dim; ++i) {
        for (US j = 0; j < A.dim; ++j) {
            if (j >= i) std::cout << A(i,j);
            else std::cout << 0;
            std::cout << ' ';
        }
    }
    std::cout << std::endl;
}

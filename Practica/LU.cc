#include "LU.hh"
LU::LU(US dim) : signP(false), N(dim) {
    A.set_dim(dim);

    P.reserve(dim);
    for (int i = 0; i < dim; ++i) P.push_back(i);

    Pt.resize(dim);
    b.resize(dim);
}

void LU::pivot(const US i) {
    US pivot_row = i;
    double pivot = 0;
    for (US j = i; j < N; ++j) {
        // maxim de la fila j
        double max = std::fabs(A(i,j));
        for (US k = j+1; k < N; ++k)
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
    for (US i = 0; i < N; ++i) { //per a cada fila
        pivot(i);
        for (US j = i+1; j < N; ++j) {
            double Mij = A(j,i)/A(i,i);
            A(j,i) = Mij;
            for (US k = i+1; k < N; ++k) A(j,k) -= Mij*A(i,k);
        }
    }
}

void LU::forward_substitution(VD& x, const VD& b) {
    x[0] = b[0];
    for (US i = 1; i < N; ++i) {
        double sum = 0;
        for (US j = 0; j < i; ++j) sum += A(i,j)*x[j];
        x[i] = (b[i] - sum);
    }
} //Lx = b

void LU::backward_substitution(VD& x, const VD& b) {
    int i = N-1;
    x[i] = b[i]/A(i,i);
    while (--i >= 0) {
        double sum = 0;
        for (US j = i+1; j < N; ++j) sum += A(i,j)*x[j];
        x[i] = (b[i] - sum)/A(i,i);
    }
} //Ux = b

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
    for (US j = 0; j < N; ++j) {
        int k = N-1;
        Ai(j,k) /= A(k,k);
        while (--k >= 0) {
            double x = 0;
            for (US s = k+1; s < N; ++s) x += A(k,s)*Ai(j,s);
            Ai(j,k) = (Ai(j,k) - x)/A(k,k);
        }

    }
}

void LU::gen_Pt() {
    for (US i = 0; i < N; ++i) Pt[P[i]] = i;
}

void LU::det() {
    detA = (signP)? -1 : 1;
    for (US i = 0; i < N; ++i) detA *= A(i,i);
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

void LU::read_b(std::ifstream& in) {
    if (in.is_open()) {
        US dim_b;
        in >> dim_b;
        if (dim_b != N) throw std::runtime_error("LU:read_b Dimension of b doesn't match");
        for (US i = 0; i < N ; ++i) in >> b[Pt[i]];
        in.close();
    }
    else throw std::runtime_error("LU::read_b File not open");
}

void LU::print_vec(std::ofstream& out, const VD& x) {
    if (out.is_open()) {
        for (US i = 0; i < x.size(); ++i) out << x[i] << '\n';
        out.close();
    }
    else throw std::runtime_error("LU::print_vec File not open");
}

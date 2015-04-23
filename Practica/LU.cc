#include "LU.hh"
LU::LU(US dim) : N(dim), signP(false) {
    A.set_dim(dim);
    P.reserve(dim);
    for (int i = 0; i < dim; ++i) P.push_back(i);

    Pt.resize(dim);
    b.resize(dim);
}

void LU::pivot(const US i) {
    US pivot_row = i;
    double pivot_el = 0;
    for (US j = i; j < N; ++j) {
        // maxim de la fila j
        double max = std::fabs(A(i,j));
        for (US k = j+1; k < N; ++k)
            if(std::fabs(A(j,k)) > max) max = std::fabs(A(j,k));
        max = std::fabs(A(j,i))/max;
        if (max > pivot_el) pivot_el = max, pivot_row = j;
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

void LU::forward_substitution(VD& x, const VD& vec) const {
    x[0] = vec[0];
    for (US i = 1; i < N; ++i) {
        double sum = 0;
        for (US j = 0; j < i; ++j) sum += A(i,j)*x[j];
        x[i] = (vec[i] - sum);
    }
} //Lx = b

void LU::backward_substitution(VD& x, const VD& vec) const {
    int i = N-1;
    x[i] = vec[i]/A(i,i);
    while (--i >= 0) {
        double sum = 0;
        for (US j = i+1; j < N; ++j) sum += A(i,j)*x[j];
        x[i] = (vec[i] - sum)/A(i,i);
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

void LU::permP(Matrix& M) const {
    US i = 0, j = 0;
    for (US k = 0; k < N; ++k) {
        j = Pt[j];
        if (j != i) M.swap_row(i,j);
        else j = i = i+1;
    }
}

void LU::det() {
    detA = (signP)? -1 : 1;
    for (US i = 0; i < N; ++i) detA *= A(i,i);
}

double LU::getEl(const US i, const US j) const {
    US k = j+1;
    double el = 0;
    if (j >= i) {
        el = A(i,j);
        k = i;
    }
    for (US l = 0; l < k; ++l) el+= A(i,l)*A(l,j);
    return el;
}

double LU::normInf() const { //PA-LU
    double norm = 0;
    for (US i = 0; i < N; ++i) { //cada fila
        double sum_i = 0;
        for (US j = 0; j < N; ++j) // cada columna
            sum_i += std::fabs(Ac(i,j) - getEl(i,j));
        if (sum_i > norm) norm = sum_i;
    }
    return norm;
}

LU::normError LU::normsAx_b(const VD& x) const {
    normError norm = {0,0,0};
    // norm(Ax-b') = norm(PAx-Pb') = norm(Ac*x - b) b' original b
    for (unsigned i = 0; i < N; ++i) {
        double Ax_ij = 0;
        for (unsigned j = 0; j < N; ++j) Ax_ij += Ac(i,j)*x[j];
        Ax_ij = std::fabs(Ax_ij - b[i]);
        norm.err1 += Ax_ij;
        norm.err2 += Ax_ij*Ax_ij;
        if (Ax_ij > norm.errInf) norm.errInf = Ax_ij;
    }
    norm.err2 = std::sqrt(norm.err2);
    return norm;
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

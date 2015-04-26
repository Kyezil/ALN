#include "LU_decomposition.hh"

LU_decomposition::LU_decomposition(const Matrix& A, std::ofstream &matLU)
: N(A.get_dim()), LU(A), signP(false) {/*{{{*/
    /* Construction */
    P.reserve(N);
    for (US i = 0; i < N; ++i) P.push_back(i);

    std::clog << "-- LU decomposition of A --" << std::endl;
    decompose();

    /* Get P transpose */
    Pt.resize(N);
    for (US i = 0; i < N; ++i) Pt[P[i]] = i;

    std::clog << "-- Output matrix LU --" << std::endl;
    LU.write(matLU);
}/*}}}*/

void LU_decomposition::pivot(const US i)
{/*{{{*/
    US pivot_row = i;
    double pivot_el = 0;
    for (US j = i; j < N; ++j) {
        // maxim de la fila j
        double max = std::fabs(LU(i,j));
        for (US k = j+1; k < N; ++k)
            if(std::fabs(LU(j,k)) > max) max = std::fabs(LU(j,k));
        max = std::fabs(LU(j,i))/max;
        if (max > pivot_el) pivot_el = max, pivot_row = j;
    }
    if (pivot_row != i) {
        LU.swap_row(i, pivot_row);
        std::swap(P[i], P[pivot_row]);
        std::clog << "    Files " << i << " <-> " << pivot_row << std::endl;
        signP = not signP;
    }
}/*}}}*/

void LU_decomposition::decompose()
{/*{{{*/
    for (US i = 0; i < N; ++i) { //per a cada fila
        pivot(i);
        for (US j = i+1; j < N; ++j) {
            double Mij = LU(j,i)/LU(i,i);
            LU(j,i) = Mij;
            for (US k = i+1; k < N; ++k) LU(j,k) -= Mij*LU(i,k);
        }
    }
}/*}}}*/

void LU_decomposition::forward_substitution(VD& x, const VD& vec) const
{/*{{{*/
    x.reserve(N);
    x.push_back(vec[P[0]]);
    for (US i = 1; i < N; ++i) {
        double sum = 0;
        for (US j = 0; j < i; ++j) sum += LU(i,j)*x[j];
        x.push_back(vec[P[i]] - sum);
    }
} //Lx = b/*}}}*/

void LU_decomposition::backward_substitution(VD& x, const VD& vec) const
{/*{{{*/
    int i = N-1;
    x[i] = vec[i]/LU(i,i);
    while (--i >= 0) {
        double sum = 0;
        for (US j = i+1; j < N; ++j) sum += LU(i,j)*x[j];
        x[i] = (vec[i] - sum)/LU(i,i);
    }
} //Ux = b/*}}}*/

void LU_decomposition::inverseA(Matrix &Ai)
{/*{{{*/
    // Solve AX = P  <=>  PAX = P  <=>  LUX = P <=> {LY=P , UX=Y}
    std::clog << "    - LY = P" << std::endl;
    for (US j = 0; j < N; ++j) {
        US k = Pt[j]; // column j has k zeros
        US i = 0;
        while (i < k) Ai.push(j,0), ++i;
        Ai.push(j,1), ++i;
        while (i < N) {
            double y = 0;
            for (US s = k; s < i; ++s) y += LU(i,s)*Ai(j,s);
            Ai.push(j,-y);
            ++i;
        }
    }

    std::clog << "    - UX = Y" << std::endl;
    for (US j = 0; j < N; ++j)
        backward_substitution(Ai(j), Ai(j));
}/*}}}*/

void LU_decomposition::solveAx_b(const VD& b, VD& x)
{/*{{{*/
    //  Ly = b
    std::clog << "   - Ly = b " << std::endl;
    forward_substitution(x, b);
    // Ux = y
    std::clog << "   - Ux = b " << std::endl;
    backward_substitution(x, x);
}/*}}}*/

double LU_decomposition::detA()
{/*{{{*/
    double det = (signP)? -1 : 1;
    for (US i = 0; i < N; ++i) det *= LU(i,i);
    return det;
}/*}}}*/

double LU_decomposition::getLU(const US i, const US j) const
{/*{{{*/
    US k = j+1;
    double el = 0;
    if (j >= i) {
        el = LU(i,j);
        k = i;
    }
    for (US l = 0; l < k; ++l) el+= LU(i,l)*LU(l,j);
    return el;
}/*}}}*/

double LU_decomposition::normInfPA_LU(const Matrix& A) const
{ //PA-LU/*{{{*/
    double norm = 0;
    for (US i = 0; i < N; ++i) { //cada fila
        double sum_i = 0;
        for (US j = 0; j < N; ++j) // cada columna
            sum_i += std::fabs(A(i,j) - getLU(Pt[i],j));
        if (sum_i > norm) norm = sum_i;
    }
    return norm;
}/*}}}*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "Chrono.hh"
#include "LU_decomposition.hh"

typedef std::vector<double> VD;

void read_vector(std::ifstream& in, VD &v) 
{/*{{{*/
    unsigned short dim;
    in >> dim;
    v.reserve(dim);
    for (int i = 0; i < dim; ++i) {
        double x;
        in >> x;
        v.push_back(x);
    }
}/*}}}*/

void print_vector(const VD &v, std::ofstream& out) 
{/*{{{*/
    for (unsigned int i = 0; i < v.size(); ++i)
        out << v[i] << '\n';
}/*}}}*/

struct normError {
    double err1, err2, errInf;
};

normError normsAx_b(const Matrix& A, const VD& x, const VD& b) 
{/*{{{*/
    normError norm = {0,0,0};
    // norm(Ax-b') = norm(PAx-Pb') = norm(Ac*x - b) b' original b
    unsigned short N = b.size();
    for (unsigned i = 0; i < N; ++i) {
        double Ax_ij = 0;
        for (unsigned j = 0; j < N; ++j) Ax_ij += A(i,j)*x[j];
        Ax_ij = std::fabs(Ax_ij - b[i]);
        norm.err1 += Ax_ij;
        norm.err2 += Ax_ij*Ax_ij;
        if (Ax_ij > norm.errInf) norm.errInf = Ax_ij;
    }
    norm.err2 = std::sqrt(norm.err2);
    return norm;
}/*}}}*/

int main() {
    Chrono timing;
    /* Llegir matriu_A.dat */
    std::ifstream matriu_in("matriu_A.dat");
    std::ofstream matriu_out("matrius_LU.dat");
    unsigned short dim;
    matriu_in >> dim;
    Matrix A (dim, matriu_in);
    LU_decomposition lu(A, matriu_out);
    matriu_in.close();
    matriu_out.close();
    /* Determinant de A */
    std::clog << "-- Compute det A --" << std::endl;
    double detA = lu.detA();
    std::clog << "    - det A = " << detA << std::endl;

    if (std::fabs(detA) > 1.e-8) {
        std::clog << "-- Inverse of A --" << std::endl;
        Matrix Ai (dim, true);
        lu.inverseA(Ai);

        std::clog << "-- Output inverse" << std::endl;
        std::ofstream inversa("inversa_A.dat");
        if (not inversa.is_open())
            throw std::runtime_error("Can't open inversa_A.dat");
        Ai.write_t(inversa);
        inversa.close();
    }
    else std::clog << "! Det A < 1.e-8 !" << std::endl;

    std::clog << "   - ||A||1" << std::endl;
    std::cout << "||A||1 = " << Matrix::norm1(A) << std::endl;

    std::clog << "   - ||A||inf" << std::endl;
    std::cout << "||A||inf = " << Matrix::normInf(A) << std::endl;

    std::clog << "   - ||PA - LU||inf" << std::endl;
    std::cout << "||PA-LU||inf = " << lu.normInfPA_LU(A) << std::endl;

    std::clog << "-- Read vector b" << std::endl;
    std::ifstream vec_in("vector_b.dat");
    VD b;
    read_vector(vec_in, b);

    std::clog << "-- Solve Ax = b for x" << std::endl;
    VD x;
    lu.solveAx_b(b, x);

    std::clog << "-- Write solution x" << std::endl;
    std::ofstream vec_out("sol_Axb.dat");
    print_vector(x, vec_out);
    vec_out.close();

    std::clog << "-- Compute norms Ax-b" << std::endl;
    normError errX = normsAx_b(A, x, b);

    std::cout << "||Ax - b||1 = " << errX.err1 << std::endl;
    std::cout << "||Ax - b||2 = " << errX.err2 << std::endl;
    std::cout << "||Ax - b||inf = " << errX.errInf << std::endl;
    std::cout << "Time elapsed " << timing.lap() << " ms" << std::endl;
}

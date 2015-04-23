#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <cassert>
#include <cmath>
#include "Chrono.hh"
#include "LU.hh"

int main() {
    Chrono timing;
    /* Llegir matriu_A.dat */
    std::ifstream matriu_in("matriu_A.dat");
    unsigned short dim;
    if (matriu_in.is_open()) matriu_in >> dim;
    else throw std::runtime_error("Can't read dimension");
    LU lu(dim);

    std::clog << "*- Lectura de la matriu A --" << std::endl;
    lu.A.read(matriu_in);
    std::clog << "-- Fi lectura de la matriu A --" << std::endl;

    /* Copia de A */
    std::clog << "*- Copia de la matriu A --" << std::endl;
    lu.Ac = lu.A;
    std::clog << "-- Fi copia de la matriu A --" << std::endl;

    /* Descomposició LU */
    std::clog << "*- Descomposició LU de A --" << std::endl;
    lu.decompose();
    std::clog << "-- Fi descomposició LU de A --" << std::endl;

    /* Escriure resultat */
    std::clog << "*- Escriptura de la matriu --" << std::endl;
    std::ofstream matriu_out("matrius_LU.dat");
    lu.A.write(matriu_out);
    std::clog << "-- Fi escriptura de la matriu --" << std::endl;

    /* Determinant de A */
    std::clog << "*- Calcul det A --" << std::endl;
    lu.det();
    std::clog << "    - det A = " << lu.detA << std::endl;
    std::clog << "-- Fi calcul det A --" << std::endl;

    if (std::fabs(lu.detA) > 1.e-8) {
        std::clog << "*- Calcul inversa de A --" << std::endl;
        lu.inverse();
        std::clog << "-- Fi calcul inversa de A --" << std::endl;

        std::clog << "*- Escriptura de la inversa" << std::endl;
        std::ofstream inversa("inversa_A.dat");
        lu.Ai.write_rev(inversa);
        std::clog << "-- Fi escriptura de la inversa" << std::endl;
    }
    else std::clog << "! Det A < 1.e-8 !" << std::endl;

    std::clog << "*- Inici d'output" << std::endl;

    std::clog << "   - det A" << std::endl;
    std::cout << "det A = " << lu.detA << std::endl;

    std::clog << "   - ||A||1" << std::endl;
    double norm1 = Matrix::norm1(lu.Ac);
    std::cout << "||A||1 = " << norm1 << std::endl;

    std::clog << "   - ||A||inf" << std::endl;
    double normInf = Matrix::normInf(lu.Ac);
    std::cout << "||A||inf = " << normInf << std::endl;

    std::clog << "*- Genera vector Pt" << std::endl;
    lu.gen_Pt();
    std::clog << "-- Fi genera vector Pt" << std::endl;

    std::clog << "*- Permuta A_copia" << std::endl;
    lu.permP(lu.Ac);
    std::clog << "-- Fi permuta A_copia" << std::endl;

    std::clog << "   - ||PA - LU||inf" << std::endl;
    std::cout << "||PA-LU||inf = " << lu.normInf() << std::endl;
    std::clog << "-- Fi d'output" << std::endl;

    std::clog << "*- Lectura de b" << std::endl;
    std::ifstream vec_in("vector_b.dat");
    lu.read_b(vec_in);
    std::clog << "-- Fi lectura de b" << std::endl;

    std::clog << "*- Càlcul Ax = b" << std::endl;

    std::clog << "   - Ly = b" << std::endl;
    std::vector<double> x (lu.N); //y = x
    lu.forward_substitution(x, lu.b);

    std::clog << "   - Ux = y" << std::endl;
    lu.backward_substitution(x, x);

    std::clog << "-- Fi càlcul Ax=b" << std::endl;

    std::clog << "*- Escriptura de x" << std::endl;
    std::ofstream vec_out("sol_Axb.dat");
    LU::print_vec(vec_out, x);
//
//    std::clog << "*- Inici d'output 2" << std::endl;
//    double errorX_1 = 0, errorX_2 = 0, errorX_inf = 0;
//    // norm(Ax-b') = norm(PAx-Pb') = norm(LUx - b)
//    {
//        for (unsigned i = 0; i < dim; ++i) {
//            double el = 0;
//            for (unsigned j = 0; j < dim; ++j) el += LU[i][j]*x[j];
//            el = std::fabs(el - b[i]);
//            errorX_1 += el;
//            errorX_2 += std::pow(el,2);
//            if (el > errorX_inf) errorX_inf = el;
//        }
//        errorX_2 = std::sqrt(errorX_2);
//    }
//    std::cout << "||Ax - b||1 = " << errorX_1 << std::endl;
//    std::cout << "||Ax - b||2 = " << errorX_2 << std::endl;
//    std::cout << "||Ax - b||inf = " << errorX_inf << std::endl;
    std::cout << "Time elapsed " << timing.lap() << " ms" << std::endl;
}

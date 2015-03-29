#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

typedef std::vector<std::vector<double> > Matriu;

void print(const Matriu& m) {
    unsigned dim = m.size();
    for (unsigned i = 0; i < dim; ++i) {
        for (unsigned j = 0; j < dim; ++j) std::cerr << m[i][j] << ' ';
        std::cerr << std::endl;
    }
}
void print_L(const Matriu& m) {
    unsigned dim = m.size();
    for (unsigned i = 0; i < dim; ++i) {
        for(unsigned j = 0; j < dim; ++j) {
            if (j > i) std::cout << 0;
            else if (j == i) std::cout << 1;
            else std::cout << m[i][j];
            std::cout << ' ';
        }
        std::cout << std::endl;
    }
}
void print_U(const Matriu& m) {
    unsigned dim = m.size();
    for (unsigned i = 0; i < dim; ++i) {
        for(unsigned j = 0; j < dim; ++j) {
            if (i > j) std::cout << 0;
            else std::cout << m[i][j];
            std::cout << ' ';
        }
        std::cout << std::endl;
    }
}

int main() {
    /* Tipus bàsic */
    Matriu A, A1, Ac; //matriu i la seva inversa
    std::vector<unsigned> row;
    bool signP = false; // signe of permutation, aka detP
    double detA;
    /* Llegir matriu_A.dat */
    std::ifstream matriu_in("matriu_A.dat");
    std::clog << "*- Lectura de la matriu A --" << std::endl;
    int dim = 0;
    if (matriu_in.is_open()) {
        matriu_in >> dim;
        std::clog << "    - dimensió de A: " << dim << std::endl;
        A.resize(dim);
        row.reserve(dim);
        // llegeix matriu A
        for (unsigned i = 0; i < dim; ++i) {
            A[i].reserve(dim);
            row.push_back(i);
            for (unsigned j = 0; j < dim; ++j) {
                double x;
                matriu_in >> x;
                A[i].push_back(x);
            }
        }
        matriu_in.close(); //tanca el flux
    }
    else std::cerr << "!!!Problema llegint matriu_A.dat!!!" << std::endl;
    std::clog << "-- Fi lectura de la matriu A --" << std::endl;

    /* Copia de A */
    std::clog << "*- Copia de la matriu A --" << std::endl;
    Ac = A;
    std::clog << "-- Fi copia de la matriu A --" << std::endl;

    /* Descomposició LU */
    std::clog << "*- Descomposició LU de A --" << std::endl;
    for (unsigned i = 0; i < dim; ++i) { //per a cada fila
        //pivotatge si cal
        {
            int pivot_row = i;
            double pivot = 0;
            for (unsigned j = i; j < dim; ++j) {
                // maxim de la fila j
                double max = std::fabs(A[i][j]);
                for (unsigned k = j+1; k < dim; ++k)
                    if(std::fabs(A[j][k]) > max) max = std::fabs(A[j][k]);
                max = std::fabs(A[j][i])/max;
                if (max > pivot) pivot = max, pivot_row = j;
            }

            if (pivot_row != i) {
                A[i].swap(A[pivot_row]);
                std::swap(row[i], row[pivot_row]);
                std::clog << "    Files " << i << " <-> " << pivot_row << std::endl;
                signP = not signP;
            }
        }

        //reducció
        for (unsigned j = i+1; j < dim; ++j) {
            double Mij = A[j][i]/A[i][i];
            A[j][i] = Mij;
            for (unsigned k = i+1; k < dim; ++k) A[j][k] -= Mij*A[i][k];
        }
    }
    std::clog << "-- Fi descomposició LU de A --" << std::endl;

    std::clog << "*- Càlcul del vector de permutació" << std::endl;
    std::vector<unsigned> perm (dim);
    for (unsigned i = 0; i < dim; ++i) perm[row[i]] = i;
    std::clog << "-- Fi càlcul vector de permutació" << std::endl;

    /* Escriure resultat */
    std::clog << "*- Escriptura de la matriu --" << std::endl;
    std::ofstream matriu_out("matrius_LU.dat");
    for (unsigned i = 0; i < dim; ++i) {
        matriu_out << A[i][0];
        for (unsigned j = 1; j < dim; ++j) matriu_out << ' ' << A[i][j];
        matriu_out << '\n';
    }
    std::clog << "-- Fi escriptura de la matriu --" << std::endl;

    /* Determinant de A */
    std::clog << "*- Calcul det A --" << std::endl;
    detA = (signP)? -1 : 1;
    for (unsigned i = 0; i < dim; ++i) detA *= A[i][i];
    std::clog << "    - det A = " << detA << std::endl;
    std::clog << "-- Fi calcul det A --" << std::endl;

    if (std::fabs(detA) > 1.e-8) {
        A1.resize(dim);
        std::clog << "*- Calcul inversa de A --" << std::endl;
        // Solve AX = I  <=>  PAX = P  <=>  LUXPt = I <=> {LY=I , UZ=Y, X=ZP}
        std::clog << "    - LY = I" << std::endl;
        for (unsigned j = 0; j < dim; ++j) {
            A1[j].reserve(dim);
            unsigned i = 0;
            while (i++ < j) A1[j].push_back(0);
            A1[j].push_back(1);
            while (i < dim) {
                double y = 0;
                for (int s = j; s < dim; ++s) y -= A[i][s]*A1[j][s];
                A1[j].push_back(y);
                ++i;
            }
        }
        std::clog << "    - UZ = Y" << std::endl;
        for (unsigned j = 0; j < dim; ++j) {
            int k = dim-1;
            A1[j][k] /= A[k][k];
            while (--k >= 0) {
                double x = 0;
                for (unsigned s = k+1; s < dim; ++s) x += A[k][s]*A1[j][s];
                A1[j][k] = (A1[j][k] - x)/A[k][k];
            }
        }
        std::clog << "    - ZP = X" << std::endl;
        std::vector<unsigned> perm_i = row;
        unsigned k = 0;
        while (k < dim) {
            if (perm_i[k] != k) {
                A1[k].swap(A1[perm_i[k]]);
                std::swap(perm_i[k], perm_i[perm_i[k]]);
            }
            else ++k;
        }
        std::clog << "*- Escriptura de la inversa" << std::endl;
        std::ofstream inversa("inversa_A.dat");
        if (inversa.is_open()) {
            for (unsigned j = 0; j < dim; ++j) {
                for (unsigned i = 0; i < dim; ++i) inversa << A1[i][j] << ' ';
                inversa << '\n';
            }
        }
        else std::cerr << "!!! Error d'escriptura !!!" << std::endl;
        std::clog << "-- Fi escriptura de la inversa" << std::endl;
    }
    else std::clog << "! Det A < 1.e-8 !" << std::endl;

    std::clog << "*- Inici d'output" << std::endl;
    std::clog << "   - det A" << std::endl;
    std::cout << "det A = " << detA << std::endl;
    std::clog << "   - ||A||1" << std::endl;
    //maximum absolut column sum;
    double norm1 = 0;
    for (unsigned j = 0; j < dim; ++j) {
        double sum_j = 0;
        for (unsigned i = 0; i < dim; ++i) sum_j += std::fabs(A[i][j]);
        if (sum_j > norm1) norm1 = sum_j;
    }
    std::cout << "||A||1 = " << norm1 << std::endl;

    std::clog << "   - ||A||inf" << std::endl;
    double normInf = 0;
    for (unsigned i = 0; i < dim; ++i) {
        double sum_i = 0;
        for (unsigned j = 0; j < dim; ++j) sum_i += std::fabs(A[i][j]);
        if (sum_i > norm1) normInf = sum_i;
    }
    std::cout << "||A||inf = " << normInf << std::endl;

    std::clog << "   - ||PA - LU||inf" << std::endl;
    {
        std::vector<unsigned> perm_i = perm;
        unsigned k = 0;
        while (k < dim) {
            if (perm_i[k] != k) {
                Ac[k].swap(Ac[perm_i[k]]);
                std::swap(perm_i[k], perm_i[perm_i[k]]);
            }
            else ++k;
        }
    }

    Matriu LU;
    LU.resize(dim);
    std::clog << "    - matriu LU" << std::endl;
    {
        for (unsigned i = 0; i < dim; ++i) {
            LU[i].reserve(dim);
            for (unsigned j = 0; j < dim; ++j) {
                unsigned k = j+1;
                double element = 0;
                if (j >= i) {
                    element = A[i][j];
                    k = i;
                }
                for (unsigned l = 0; l < k; ++l)
                    element += A[i][l]*A[l][j];
                LU[i][j] = element;
            }
        }
    }
        double normErrorInf = 0;
    {
        for (unsigned i = 0; i < dim; ++i) {
            double sum_i = 0;
            for (unsigned j = 0; j < dim; ++j)
                sum_i += std::fabs(Ac[i][j] - LU[i][j]);
            if (sum_i > normErrorInf) normErrorInf = sum_i;
        }
    }
    std::cout << "||PA-LU||inf = " << normErrorInf << std::endl;
    std::clog << "-- Fi d'output" << std::endl;


    std::clog << "*- Lectura de b" << std::endl;
    std::vector<double> b(dim);
    std::ifstream vec_in;
    vec_in.open("vector_b.dat");
    if (vec_in.is_open()) {
        unsigned dimB;
        vec_in >> dimB;
        for (unsigned i = 0; i < dimB; ++i) vec_in >> b[perm[i]];
        vec_in.close();
    }
    else std::cerr << "!!!Problema llegint vector_b.dat!!!" << std::endl;
    std::clog << "-- Fi lectura de b" << std::endl;

    std::clog << "*- Càlcul Ax = b" << std::endl;
    std::clog << "   - Ly = b" << std::endl;
    std::vector<double> x; //y = x
    {
        x.reserve(dim);
        x.push_back(b[0]);
        for (unsigned i = 1; i < dim; ++i) {
            double sum = 0;
            for (unsigned j = 0; j < i; ++j) sum += A[i][j]*x[j];
            x[i] = b[i] - sum;
        }

        std::clog << "   - Ux = y" << std::endl;
        int i = dim-1;
        x[i] = x[i]/A[i][i];
        while (--i >= 0) {
            double sum = 0;
            for (unsigned j = i+1; j < dim; ++j) sum += A[i][j]*x[j];
            x[i] = (x[i] - sum)/A[i][i];
        }
    }
    std::clog << "-- Fi càlcul Ax=b" << std::endl;
    
    std::clog << "*- Escriptura de x" << std::endl;
    {
        std::ofstream vec_out;
        vec_out.open("sol_Axb.dat");
        if (vec_out.is_open()) {
            for (unsigned i = 0; i < dim; ++i) vec_out << x[i] << '\n';
        }
        else std::cerr << "!!!Problema escrivint sol_Axb.dat" << std::endl;
    }
    
    std::clog << "*- Inici d'output 2" << std::endl;
    double errorX_1 = 0, errorX_2 = 0, errorX_inf = 0;
    // norm(Ax-b') = norm(PAx-Pb') = norm(LUx - b)
    {
        for (unsigned i = 0; i < dim; ++i) {
            double el = 0;
            for (unsigned j = 0; j < dim; ++j) el += LU[i][j]*x[j];
            el = std::fabs(el - b[i]);
            errorX_1 += el;
            errorX_2 += std::pow(el,2);
            if (el > errorX_inf) errorX_inf = el;
        }
        errorX_2 = std::sqrt(errorX_2);
    }
    std::cout << "||Ax - b||1 = " << errorX_1 << std::endl;
    std::cout << "||Ax - b||2 = " << errorX_2 << std::endl;
    std::cout << "||Ax - b||inf = " << errorX_inf << std::endl;
}

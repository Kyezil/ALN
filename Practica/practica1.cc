#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

typedef std::vector<std::vector<double> > Matriu;

int main() {
    /* Tipus bàsic */
    Matriu A, A1; //matriu i la seva inversa
    std::vector<int> row;
    bool signP = false; // signe of permutation, aka detP

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
    Matriu Ac = A;
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

    /* Escriure resultat */
    std::clog << "*- Escriptura de la matriu --" << std::endl;
    std::ofstream matriu_out("matrius_LU.dat");
    for (unsigned i = 0; i < dim; ++i) {
        matriu_out << A[i][i];
        for (unsigned j = 1; j < dim; ++j) matriu_out << ' ' << A[i][j];
        matriu_out << '\n';
    }
    std::clog << "-- Fi escriptura de la matriu --" << std::endl;

    /* Determinant de A */
    std::clog << "*- Calcul det A --" << std::endl;
    double detA = (signP)? -1 : 1;
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
        std::vector<int> perm = row;
        unsigned k = 0;
        while (k < dim) {
            if (perm[k] != k) {
                A1[k].swap(A1[perm[k]]);
                std::swap(perm[k], perm[perm[k]]);
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
}

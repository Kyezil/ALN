#include <iostream>
#include <fstream>
#include <vector>

typedef std::vector<std::vector<double> > Matriu;

int main() {
    /* Tipus bàsic */
    Matriu A;
    std::vector<int> row;
   
    /* Llegir matriu_A.dat */
    std::ifstream matriu("matriu_A.dat");
    std::clog << "-- Lectura de la matriu A --" << std::endl;
    int dim = 0;
    if (matriu.is_open()) {
        matriu >> dim;
        std::clog << "    - dimensió de A: " << dim << std::endl;
        A.resize(dim);
        row.resize(dim);
        // llegeix matriu A
        for (unsigned i = 0; i < dim; ++i) {
            A[i].resize(dim);
            row[i] = i;
            for (unsigned j = 0; j < dim; ++j) {
                matriu >> A[i][j];
            }
        }
        matriu.close(); //tanca el flux
    }
    else std::cerr << "!!!Problema llegint matriu_A.dat!!!" << std::endl;
    std::clog << "-- Fi Lectura de la matriu A --" << std::endl; 

    /* Copia de A */
    std::clog << "-- Copia de la matriu A --" << std::endl;
    Matriu Ac = A;
    std::clog << "-- Fi Copia de la matriu A --" << std::endl;    
    
    /* Descomposició LU */
    std::clog << "-- Descomposició LU de A --" << std::endl;
}

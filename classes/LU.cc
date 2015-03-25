#include "LU.hh"
void LU::partial_pivoting(const unsigned i) {
    double max_pivot = 0;
    unsigned pivot_row = i;
    for (int j = i; j < mat.N; ++j) {
        //get max element of row j
        double max = std::abs(mat(j,i));
        for (int k = j+1; k < mat.N; ++k)
            if (std::abs(mat(j,k)) > max) max = std::abs(mat(j,k));
        if (max > max_pivot) {
            max_pivot = max;
            pivot_row = j;
        }
    }
    if(pivot_row != i) mat.swap_row(i, pivot_row);
}

void LU::partial_scaled_pivoting(const unsigned i) {
    //Permut row, scaled partial pivoting
    double max_pivot = 0;
    int pivot_row = i;
    for (int j = i; j < mat.N; ++j) {
        //get max element of row j
        double max = std::abs(mat(j,i));
        for (int k = j+1; k < mat.N; ++k)
            if (std::abs(mat(j,k)) > max) max = std::abs(mat(j,k));
        max = std::abs(mat(j,i))/max;
        if (max > max_pivot) {
            max_pivot = max;
            pivot_row = j;
        }
    }
    if (pivot_row != i) mat.swap_row(i, pivot_row);
}

void LU::total_pivoting(const unsigned i) {
    //Permut row and column, total pivoting
    double max_pivot = 0;
    int pivot_row = i, pivot_col = i;
    for (int j = i; j < mat.N; ++j) {
        for (int k = j; k < mat.N; ++k) {
            if (std::abs(mat(j,k)) > max_pivot) {
                max_pivot = std::abs(mat(j,k));
                pivot_row = j;
                pivot_col = k;
            }
        }
    }
    if(pivot_row != i) mat.swap_row(i, pivot_row);
    //if(pivot_col != i) mat.swap_col(i, pivot_col);
}
/* define Class LU */

LU::LU(const unsigned n) : mat(n) {}

double& LU::operator()(unsigned i, unsigned j) {
    return mat(i,j);
}

void LU::factorize(){
    //For each row
    for (int i = 0; i < mat.N; ++i) {
        // pivot if needed
        partial_scaled_pivoting(i);
        // reduction
        for (int j = i+1; j < mat.N; ++j) {
            double Mij = mat(j,i) / mat(i,i);
            mat(j,i) = Mij;
            for (int k = i+1; k < mat.N; ++k) mat(j,k) -= Mij*mat(i,k);
        }
    }
}

void LU::read() {
    mat.read();
    factorize();
}

void LU::print_L() const {
    std::cout.precision(OUT_DIGITS);
    std::cout.setf(std::ios::fixed);
    std::cout << "Matrix L" << std::endl;
    for (int i = 0; i < mat.N; ++i) {
        for (int j = 0; j < mat.N; ++j) {
            std::cout << std::right << std::setw(10);
            if (i < j) std::cout << 0;
            else if (i == j) std::cout << 1;
            else std::cout << mat(i,j);
        }
        std::cout << std::endl;
    }
}

void LU::print_U() const {
    std::cout.precision(OUT_DIGITS);
    std::cout.setf(std::ios::fixed);
    std::cout << "Matrix U" << std::endl;
    for (int i = 0; i < mat.N; ++i) {
        for (int j = 0; j < mat.N; ++j) {
            std::cout << std::right << std::setw(10);
            if (i > j) std::cout << 0;
            else std::cout << mat(i,j);
        }
        std::cout << std::endl;
    }
}

void LU::print_P() const {
    std::cout << "Matrix P" << std::endl;
    for (int i = 0; i < mat.N; ++i) {
        for (int j = 0; j < mat.N; ++j) {
            if (j != 0) std::cout << ' ';
            if (mat.rows[i] == j) std::cout << 1;
            else std::cout << 0;
        }
        std::cout << std::endl;
    }
}

void LU::check() const {
    std::cout << "Matrix P'LU" << std::endl;
    std::vector<int> P2 (mat.N);
    for (int i = 0; i < mat.N; ++i) P2[mat.rows[i]] = i;

    for (int i = 0; i < mat.N; ++i) {
        //Multiplication
        for (int j = 0; j < mat.N; ++j) {
            std::cout << std::right << std::setw(10);
            double elem = 0;
            int k = 0;
            while (k < P2[i] and k <= j) {
                elem += mat(P2[i],k)*mat(k,j);
                ++k;
            }
            if (P2[i] <= j) elem += mat(P2[i],j);
            std::cout << elem;
        }
        std::cout << std::endl;
    }
}

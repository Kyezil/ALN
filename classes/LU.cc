#include "LU.hh"

LU::Pos LU::partial_pivoting(Matrix& mat, const unsigned i) {
    double max_pivot = 0;
    unsigned pivot_row = i;
    for (int j = i; j < mat.N; ++j) {
        //get max element of row j
        double max = std::abs(mat(j,i));
        for (int k = j+1; k < mat.M; ++k)
            if (std::abs(mat(j,k)) > max) max = std::abs(mat(j,k));
        if (max > max_pivot) {
            max_pivot = max;
            pivot_row = j;
        }
    }

    return std::make_pair(pivot_row, i);
}

LU::Pos LU::partial_scaled_pivoting(Matrix& mat, const unsigned i) {
    //Permut row, scaled partial pivoting
    double max_pivot = 0;
    Pos piv;
    piv.first = piv.second = i;
    for (int j = i; j < mat.N; ++j) {
        //get max element of row j
        double max = std::abs(mat(j,i));
        for (int k = j+1; k < mat.M; ++k)
            if (std::abs(mat(j,k)) > max) max = std::abs(mat(j,k));
        max = std::abs(mat(j,i))/max;
        if (max > max_pivot) {
            max_pivot = max;
            piv.second = j;
        }
    }
    return piv;
}

LU::Pos LU::total_pivoting(Matrix& mat, const unsigned i) {
    //Permut row and column, total pivoting
    double max_pivot = 0;
    Pos piv;
    piv.first = piv.second = i;
    for (int j = i; j < mat.N; ++j) {
        for (int k = j; k < mat.M; ++k) {
            if (std::abs(mat(j,k)) > max_pivot) {
                max_pivot = std::abs(mat(j,k));
                piv.first = j;
                piv.second = k;
            }
        }
    }
    return piv;
}
/* define Class LU */
LU::LU() {}

LU::LU(const unsigned n) : mat(n) {}

void LU::descompose(Pos (*f)(Matrix& mat, const unsigned i)){
    //For each row
    for (int i = 0; i < mat.N; ++i) {
        // pivot if needed
        Pos piv = (*f)(mat, i);
        if (piv.first != i) mat.perm_row(i, piv.first);
        if (piv.second != i) mat.perm_col(i, piv.second);
        // reduction
        for (int j = i+1; j < mat.N; ++j) {
            double Mij = mat(j,i) / mat(i,i);
            mat(j,i) = Mij;
            for (int k = i+1; k < mat.M; ++k) mat(j,k) -= Mij*mat(i,k);
        }
    }
}

void LU::read() {
    mat.read();
    descompose(partial_scaled_pivoting);
}

void LU::print_L() const {
    std::cout.precision(OUT_DIGITS);
    std::cout.setf(std::ios::fixed);
    std::cout << "Matrix L" << std::endl;
    for (int i = 0; i < mat.N; ++i) {
        for (int j = 0; j < mat.M; ++j) {
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
        for (int j = 0; j < mat.M; ++j) {
            std::cout << std::right << std::setw(10);
            if (i > j) std::cout << 0;
            else std::cout << mat(i,j);
        }
        std::cout << std::endl;
    }
}

void LU::print_P() const {
    std::cout << "Matrix P" << std::endl;
    const std::vector<int> & rows = mat.get_row_perm();
    const std::vector<int> & cols = mat.get_col_perm();
    for (int i = 0; i < mat.N; ++i) {
        for (int j = 0; j < mat.M; ++j) {
            if (j != 0) std::cout << ' ';
            if (rows[i] == cols[j]) std::cout << 1;
            else std::cout << 0;
        }
        std::cout << std::endl;
    }
}

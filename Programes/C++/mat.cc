#include "mat.hh"
Mat::Mat(const int nr, const int nc) :
    rows_(nr), cols_(nc), data_(0.0, nr * nc) {}

int Mat::rows() const {
    return rows_;
}

int Mat::cols() const {
    return cols_;
}

std::valarray<double> Mat::row(const int r) const {
    return data_[std::slice((r-1) * cols_, cols_, 1)];
}

std::valarray<double> Mat::col(const int c) const {
    return data_[std::slice(c-1, rows_, cols_)];
}

std::valarray<double> Mat::diag() const {
    return data_[std::slice(0, rows_, cols_+1)];
}

std::slice_array<double> Mat::row(const int r) {
    return data_[std::slice((r-1) * cols_, cols_, 1)];
}

std::slice_array<double> Mat::col(const int c) {
    return data_[std::slice(c-1, rows_, cols_)];
}

std::slice_array<double> Mat::diag() {
    return data_[std::slice(0, rows_, cols_+1)];
}

double& Mat::operator()(const int r, const int c) {
    return data_[(r-1) * cols_ + c-1];
}

double Mat::operator()(const int r, const int c) const {
    return data_[(r-1) * cols_ + c-1];
}

std::valarray<double> Mat::operator[] (std::slice s) const {
    return data_[s];
}

std::slice_array<double> Mat::operator[](std::slice s) {
    return data_[s];
}

Mat& Mat::operator*=(const Mat& B) {
    assert(cols() == B.rows() and cols() == B.cols());;
    for (int i = 1; i <= rows(); ++i) {
        for (int j = 1; j <= cols(); ++j) {
            double sum = 0;
            for (int k = 1; k <= cols(); ++k) sum += (*this)(i,k)*B(k,j);
            (*this)(i,j) = sum;
        }
    }
    return *this;
}

void Mat::swap_row(const int r1, const int r2) {
    std::valarray<double> tmp = row(r1);
    row(r1) = row(r2);
    row(r2) = tmp;
}

void Mat::swap_col(const int c1, const int c2) {
    std::valarray<double> tmp = col(c1);
    col(c1) = col(c2);
    col(c2) = tmp;
}

Mat Mat::transpose(const Mat& A) {
    Mat result(A.cols(), A.rows());
    for (int i = 1; i <= A.rows(); ++i)
        result.col(i) = A.row(i);
    return result;
}

void Mat::fwsb(const Mat& L, Mat& x, const Mat& b) {
    int n = x.rows();
    x(1) = b(1);
    for (int i = 1; i <= n; ++i) {
        double sum = 0;
        for (int j = 1; j < i; ++j) sum += L(i,j)*x(j);
        x(i) = b(i) - sum;
    }
}

void Mat::bwsb(const Mat& U, Mat& x, const Mat& b) {
    int n = x.rows();
    x(n) = b(n)/U(n,n);
    for (int i = n-1; i >= 1; --i) {
        double sum = 0;
        for (int j = i+1; j <= n; ++j) sum += U(i,j)*x(j);
        x(i) = (b(i) - sum)/U(i,i);
    }
}

double Mat::norm1(const Mat &mat) {
    double norm = 0;
    for (int j = 1; j <= mat.cols(); ++j) {
        double sum_j = 0;
        for (int i = 1; i <= mat.rows(); ++i) sum_j += std::fabs(mat(i,j));
        if (sum_j > norm) norm = sum_j;
    }
    return norm;
}

double Mat::normInf(const Mat &mat) {
    double norm = 0;
    for (int i = 1; i <= mat.rows(); ++i) {
        double sum_i = 0;
        for (int j = 1; j <= mat.cols(); ++j) sum_i += std::fabs(mat(i,j));
        if (sum_i > norm) norm = sum_i;
    }
    return norm;
}

double Mat::norm1(const std::valarray<double>& d) {
    double sum = 0;
    for (int i = 0; i < d.size(); ++i) sum += fabs(d[i]);
    return sum;
}

double Mat::normInf(const std::valarray<double>& d) {
    double norm = 0;
    for (int i = 0; i < d.size(); ++i) {
        double el = fabs(d[i]);
        if (el > norm) norm = el;
    }
    return norm;
}

double Mat::norm2(const std::valarray<double>& d) {
    double norm = 0;
    for (int i = 0; i < d.size(); ++i)  norm += d[i]*d[i];
    return std::sqrt(norm);
}
void Mat::printOctave(const Mat& mat, std::ostream& out) {
    int m = mat.rows();
    int n = mat.cols();
    out << '[';
    for (int i = 1; i <= m; ++i) {
        if (i > 1) out << ";\n";
        if (n >= 1) out << mat(i,1);
        for (int j = 2; j <= n; ++j)
            out << ',' << mat(i,j);
    }
    out << ']';
}
Mat operator*(const Mat& A, const Mat& B) {
    assert(A.cols() == B.rows());;
    Mat C (A.rows(), B.cols());
    for (int i = 1; i <= C.rows(); ++i) {
        for (int j = 1; j <= C.cols(); ++j) {
            double sum = 0;
            for (int k = 1; k <= A.cols(); ++k) sum += A(i,k)*B(k,j);
            C(i,j) = sum;
        }
    }
    return C;
}
/* IN/OUT OPERATIONS */
std::ostream& operator<<(std::ostream& os, const Mat& mat) {
    if (mat.rows() < 1 or mat.cols() < 1) os << "[ ]";
    else {
        for (int i = 1; i <= mat.rows(); ++i) {
            os << '|' << mat(i,1);
            for (int j = 2; j <= mat.cols(); ++j)
                os << ' ' << mat(i,j);
            os << "|\n";
        }
    }
    return os;
}

std::istream& operator>>(std::istream& in, Mat& mat) {
    for (int i = 1; i <= mat.rows(); ++i)
        for (int j = 1; j <= mat.cols(); ++j)
            in >> mat(i,j);
    return in;
}

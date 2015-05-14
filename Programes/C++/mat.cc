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

std::slice_array<double> Mat::row(const int r) {
    return data_[std::slice((r-1) * cols_, cols_, 1)];
}

std::slice_array<double> Mat::col(const int c) {
    return data_[std::slice(c-1, rows_, cols_)];
}

double& Mat::operator()(const int r, const int c) {
    return data_[(r-1) * cols_ + c-1];
}

double Mat::operator()(const int r, const int c) const {
    return data_[(r-1) * cols_ + c-1];
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

Mat Mat::transpose() {
    Mat result(cols_, rows_);
    for (int i = 0; i < rows_; ++i)
        result.col(i) = static_cast<std::valarray<double> > (row(i));
    return result;
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

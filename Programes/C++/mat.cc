#include "mat.hh"
Mat::Mat(const int nr, const int nc) :
    rows_(nr), cols_(nc), data_(nr * nc) {}

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

Mat Mat::transpose() {
    Mat result(cols_, rows_);
    for (int i = 0; i < rows_; ++i)
        result.col(i) = static_cast<std::valarray<double> > (row(i));
    return result;
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

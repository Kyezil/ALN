#include "mat.hh"
Mat::Mat(const int rows, const int columns) :
    rows_(rows), cols_(columns), data_(rows * columns) {}

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

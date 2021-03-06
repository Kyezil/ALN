#ifndef MAT_HH
#define MAT_HH
#include <valarray>
#include <cassert>
#include <iostream>
class Mat {
    public:
        // creates an empty rows x size matrix
        Mat(const int rows, const int cols);

        // get the number of rows in the Mat
        int rows() const;
        // get the number of columns in the Mat
        int cols() const;

        // retrieve the data from row r of the matrix
        std::valarray<double> row(const int r) const;
        // retrieve the data from col c of the matrix
        std::valarray<double> col(const int c) const;
        // retrieve data to diag
        std::valarray<double> diag() const;

        // retrieve refernce to the data from row r of the matrix
        std::slice_array<double> row(const int r);
        // retrieve refernce to the data from col c of the matrix
        std::slice_array<double> col(const int c);
        // retrieve reference to diag
        std::slice_array<double> diag();

        // basic item reference
        double & operator()(const int r, const int c = 1);
        // basic item retrieval
        double operator()(const int r, const int c = 1) const;
        
        // advanced item retrieval
        std::valarray<double> operator[] (std::slice s) const;
        std::slice_array<double> operator[](std::slice s);

        // multiply
        Mat& operator*=(const Mat& B);

        // permuta dues files/columnes
        void swap_row(const int r1, const int r2);
        void swap_col(const int c1, const int c2);

        // genetate a new matrix that is the transposition of this one
        static Mat transpose(const Mat& A);

        // forward substitution
        static void fwsb(const Mat& L, Mat& X, const Mat& B);
        // backward substitution
        static void bwsb(const Mat& U, Mat& X, const Mat& B);

        // normes matricials
        static double norm1(const Mat &mat);
        static double normInf(const Mat &mat);
        // normes vectorials
        static double norm1(const std::valarray<double>& d);
        static double normInf(const std::valarray<double>& d);
        static double norm2(const std::valarray<double>& d);
        static void printOctave(const Mat& m, std::ostream& out);
    protected:
        int rows_;
        int cols_;
        std::valarray<double> data_;
};
// OPERATORS
Mat operator*(const Mat& A, const Mat& B);
// IN/OUT
std::ostream& operator<<(std::ostream& os, const Mat& mat);
std::istream& operator>>(std::istream& in, Mat& mat);
#endif

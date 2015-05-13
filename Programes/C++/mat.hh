#ifndef MAT_HH
#define MAT_HH
#include <valarray>

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

        // retrieve refernce to the data from row r of the matrix
        std::slice_array<double> row(const int r);
        // retrieve refernce to the data from col c of the matrix
        std::slice_array<double> col(const int c);

        // basic item reference
        double & operator()(const int r, const int c);
        // basic item retrieval
        double operator()(const int r, const int c) const;

        // genetate a new matrix that is the transposition of this one
        Mat transpose();

    protected:
        int rows_;
        int cols_;
        std::valarray<double> data_;
};
#endif

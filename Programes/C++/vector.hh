#ifndef VECTOR_HH
#define VECTOR_HH
#include <cassert>
class Vector {
    private:
        double * m_v;
        int m_size;
    public:
        Vector(int size);
        Vector(Vector const &other);
        Vector(Vector &&other);
        ~Vector();

        Vector& operator=(Vector const &other);
        Vector& operator=(Vector const &&other);
        Vector& operator+(Vector const &other);
        Vector& operator-(Vector const &other);
        double operator*(Vector const &other);

        double operator()(int i) const;
        double& operator()(int i);

        inline void swap(int i, int j);

        int size() const;

        static double norm1(const Vector &v);
        static double norm2(const Vector &v);
        static double normInf(const Vector &v);
};
#endif

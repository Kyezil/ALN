#include "vector.hh"
Vector::Vector(int c_size) : m_size(c_size) {
    m_v = new double [m_size];
}
Vector::Vector(Vector const &other) : m_size(other.m_size) {
    m_v = new double [m_size];
    for (int i = 0; i < m_size; ++i) m_v[i] = other.m_v[i];
}
Vector::Vector(Vector &&other) : m_v(other.m_v), m_size(other.m_size) {
    other.m_size = 0;
    other.m_v = nullptr;
}
Vector::~Vector(){
    if (m_v != nullptr) delete[] m_v;
}

Vector& Vector::operator=(Vector const &other){}
Vector& Vector::operator=(Vector const &&other) {
    if (this != &other) {
        delete[] m_v;
        m_size = other.m_size;
        m_v = other.m_v;
        other.m_v = nullptr;
    }
}
Vector& Vector::operator+(Vector const &other){}
Vector& Vector::operator-(Vector const &other){}
double Vector::operator*(Vector const &other){}

double Vector::operator[](int i) const{}
double& Vector::operator[](int i){}

void Vector::swap(int i, int j){}

int Vector::size() const{}

double Vector::norm1(const Vector &v){}
double Vector::norm2(const Vector &v){}
double Vector::normInf(const Vector &v){}

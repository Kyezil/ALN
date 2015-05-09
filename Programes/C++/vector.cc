#include "vector.hh"
Vector::Vector(int c_size) {
    m_v.resize(c_size);
}
Vector& Vector::operator+(Vector const &other) {
    assert(m_v.size() == other.m_v.size());
    for (int i = 0; i < m_v.size(); ++i)
        m_v[i] = m_v[i] + other.m_v[i];
}
Vector& Vector::operator-(Vector const &other) {
    assert(m_v.size() == other.m_v.size());
    for (int i = 0; i < m_v.size(); ++i)
        m_v[i] = m_v[i] - other.m_v[i];
}
double Vector::operator*(Vector const &other) { 
    assert(m_v.size() == other.m_v.size());
    double dot = 0;
    for (int i = 0; i < m_v.size(); ++i)
        dot +=  m_v[i]*other.m_v[i];
}

double Vector::operator[](int i) const { return m_v[i]; }
double& Vector::operator[](int i) { return m_v[i]; }

void Vector::swap(int i, int j) { swap(m_v[i],m_v[j]); }

int Vector::size() const { return m_v.size(); }

double Vector::norm1(const Vector &v) {
    double norm = 0;
    for (int i = 0; i < v.m_v.size(); ++i)
        norm += fabs(v.m_v[i]);
    return norm;
}
double Vector::norm2(const Vector &v) {
    double norm = 0;
    for (int i = 0; i < v.m_v.size(); ++i)
        norm += v.m_v[i]*v.m_v[i];
    return sqrt(norm);
}
double Vector::normInf(const Vector &v) {
    double norm = 0;
    for (int i = 0; i < v.m_v.size(); ++i) {
        double el = fabs(v.m_v[i]);
        if (el > norm) norm = el;
    }
    return norm;
}

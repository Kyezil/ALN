#include "vector.hh"
Vector::Vector(int c_size) {
    m_v.resize(c_size);
}
Vector Vector::operator+(Vector const &other) {
    assert(m_v.size() == other.m_v.size());
    Vector res(m_v.size());
    for (int i = 0; i < res.m_v.size(); ++i)
        res.m_v[i] = m_v[i] + other.m_v[i];
    return res;
}
Vector Vector::operator-(Vector const &other) {
    assert(m_v.size() == other.m_v.size());
    Vector res(m_v.size());
    for (int i = 0; i < res.m_v.size(); ++i)
        res.m_v[i] = m_v[i] -  other.m_v[i];
    return res;
}
Vector& Vector::operator+=(Vector const &other) {
    assert(m_v.size() == other.m_v.size());
    for (int i = 0; i < m_v.size(); ++i)
        m_v[i] += other.m_v[i];
    return *this;
}
Vector& Vector::operator-=(Vector const &other) {
    assert(m_v.size() == other.m_v.size());
    for (int i = 0; i < m_v.size(); ++i)
        m_v[i] -= other.m_v[i];
    return *this;
}
double Vector::operator*(Vector const &other) { 
    assert(m_v.size() == other.m_v.size());
    double dot = 0;
    for (int i = 0; i < m_v.size(); ++i)
        dot +=  m_v[i]*other.m_v[i];
    return dot;
}

double Vector::operator[](int i) const { return m_v[i]; }
double& Vector::operator[](int i) { return m_v[i]; }

void Vector::swap(int i, int j) { swap(m_v[i],m_v[j]); }

int Vector::size() const { return m_v.size(); }

void Vector::print(std::ostream& os, Vector const &v) {
    int n = v.m_v.size();
    os << '[';
    if (n > 1) {
        os << v.m_v[0];
        for (int i = 1; i < v.m_v.size(); ++i)
            os << ',' << v.m_v[i];
    }
    os << "]\n";
}

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

// NON MEMBER FUNCTIONS
std::ostream& operator<<(std::ostream& os, Vector const &v) {
    int n = v.m_v.size();
    if (n > 1) {
        os << v.m_v[0];
        for (int i = 1; i < v.m_v.size(); ++i)
            os << ' ' << v.m_v[i];
    }
    return os;
}

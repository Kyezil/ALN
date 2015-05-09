#include "vector.hh"
Vector::Vector(int size){}
Vector::Vector(Vector const &other){}
Vector::Vector(Vector &&other){}
Vector::~Vector(){}

Vector& Vector::operator=(Vector const &other){}
Vector& Vector::operator=(Vector const &&other){}
Vector& Vector::operator+(Vector const &other){}
Vector& Vector::operator-(Vector const &other){}
double Vector::operator*(Vector const &other){}

double Vector::operator()(int i, int j) const{}
double& Vector::operator()(int i, int j){}

void Vector::swap(int i, int j){}

int Vector::size() const{}

double Vector::norm1(const Vector &v){}
double Vector::norm2(const Vector &v){}
double Vector::normInf(const Vector &v){}

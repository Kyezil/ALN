#ifndef VECTOR_HH
#define VECTOR_HH
#include <vector>
#include <cmath>
#include <cassert>
#include <ostream>
class Vector {
    private:
        std::vector<double> m_v;
    public:
        // Crea un vector de mida c_size
        Vector(int c_size);

        // OPERACIONS VECTORIALS
        Vector operator-();
        Vector operator+(Vector const &other);
        Vector operator-(Vector const &other);
        Vector& operator+=(Vector const &other);
        Vector& operator-=(Vector const &other);
        double operator*(Vector const &other); //producte escalar

        // OPERACIONS PER ESCALARS
        Vector operator*(double a);
        Vector operator/(double a);
        Vector& operator*=(double a);
        Vector& operator/=(double a);

        // Accés element rvalue
        double operator[](int i) const;
        // Accés element lvalue
        double& operator[](int i);
        // Output
        friend std::ostream& operator<<(std::ostream& os, Vector const &v);

        // Permuta 2 elements
        void swap(int i, int j);

        // Consulta la mida
        int size() const;

        // Print vector [#,#,...,#]
        static void print(std::ostream& os, Vector const &v);
        // Càlcul de normes convencionals
        static double norm1(const Vector &v);
        static double norm2(const Vector &v);
        static double normInf(const Vector &v);
};
#endif

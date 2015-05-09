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
        Vector(int const c_size);

        // OPERACIONS VECTORIALS
        Vector operator-() const;
        Vector operator+(Vector const &other) const;
        Vector operator-(Vector const &other) const;
        Vector& operator+=(Vector const &other);
        Vector& operator-=(Vector const &other);
        double operator*(Vector const &other) const; //producte escalar

        // OPERACIONS PER ESCALARS
        Vector operator*(double const a) const;
        Vector operator/(double const a) const;
        Vector& operator*=(double const a);
        Vector& operator/=(double const a);

        // Accés element rvalue
        double operator[](int const i) const;
        // Accés element lvalue
        double& operator[](int const i);
        // Output
        friend std::ostream& operator<<(std::ostream& os, Vector const &v);

        // Permuta 2 elements
        void swap(int const i, int const j);

        // Consulta la mida
        int size() const;

        // Print vector [#,#,...,#]
        static void print(std::ostream& os, Vector const &v);
        // Càlcul de normes convencionals
        static double norm1(Vector const &v);
        static double norm2(Vector const &v);
        static double normInf(Vector const &v);
};
#endif

#ifndef VECTOR_HH
#define VECTOR_HH
#include <cassert>
class Vector {
    private:
        double * m_v;
        int m_size;
    public:
        // Crea un vector de mida c_size
        Vector(int c_size);
        // Crea una copia de other
        Vector(Vector const &other);
        // Crea per desplaçament
        Vector(Vector &&other);
        // Destructor
        ~Vector();

        // Assignació
        Vector& operator=(Vector const &other);
        // Desplaçament
        Vector& operator=(Vector const &&other);
        // Suma convencional
        Vector& operator+(Vector const &other);
        // Resta convencional
        Vector& operator-(Vector const &other);
        // Producte escalar de vectors
        double operator*(Vector const &other);

        // Accés element rvalue
        double operator[](int i) const;
        // Accés element lvalue
        double& operator[](int i);

        // Permuta 2 elements
        void swap(int i, int j);

        // Consulta la mida
        int size() const;

        // Càlcul de normes convencionals
        static double norm1(const Vector &v);
        static double norm2(const Vector &v);
        static double normInf(const Vector &v);
};
#endif

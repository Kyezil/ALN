#include <iostream>
#include <valarray>
using namespace std;

typedef valarray<double> vec;

void printOctave(const vec& v) {
    cout << '[';
    if (v.size() >= 1) cout << v[0];
    for (int i = 1; i < v.size(); ++i) cout << ',' << v[i];
    cout << "]\n";
}

double dot(const vec& a, const vec& b) {
    double ret = 0;
    for (int i = 0; i < a.size(); ++i) ret += a[i]*b[i];
    return ret;
}

ostream& operator<<(ostream& os, const vec& a) {
    int n = a.size();
    if (n > 1) os << a[0];
    for (int i = 1; i < a.size(); ++i) os << ' ' << a[i];
    return os;
}

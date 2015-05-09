#include <iostream>
#include <cmath>
using namespace std;

pair<double, double> solve1(double a, double b, double c) {
    // solució amb formula de sempre
    double arr = sqrt(b*b-4*a*c);
    return make_pair((-b+arr)/(2*a), (-b-arr)/(2*a));
}

pair<double, double> solve2(double a, double b, double c) {
    // evita cancelació de b^2 amb sqrt(b^2 - 4ac)
    double arr = sqrt(b*b-4*a*c);
    if (b > 0) return make_pair(2*c/(-b-arr),(-b-arr)/(2*a));
    else return make_pair((-b+arr)/(2*a),2*c/(-b+arr));
}

pair<double, double> solve3(double a, double b, double c) {
    // vieta formula molt millor si x1 >> x2
    // x1 + x2 = -b/a       x1 * x2 = c/a
    // x1 >> x2 => x1 ~= -b/a   =>  x1 ~= c/-b
    return make_pair(-b/a, c/-b);
}

int main() {
    double a,b,c;
    cin >> a >> b >> c;
    pair<double, double> sol;
    sol = solve1(a,b,c);
    printf("(%e,%e)\n", sol.first, sol.second);
    // more eficient
    sol = solve2(a,b,c);
    printf("(%e,%e)\n", sol.first, sol.second);
    // even eficient if b >> c and simpler...
    sol = solve3(a,b,c);
    printf("(%e,%e)\n", sol.first, sol.second);
}

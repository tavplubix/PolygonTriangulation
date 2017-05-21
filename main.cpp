#include <iostream>
#include <vector>
#include <iomanip>

#include "Polygon.h"

int main() {
    size_t n;
    std::cin >> n;
    std::vector<std::pair<double, double>> a(n);
    for (int i = 0; i < n; ++i) {
        double x, y;
        std::cin >> x >> y;
        a[i].first = x;
        a[i].second = y;
    }
    Polygon pol(a.begin(), a.end());

    std::vector<Edge> t;
    std::cout << pol.triangulation(t) << '\n';
    for (const auto &i : t)
        std::cout << i.first.n << ' ' << i.second.n << '\n';

    return 0;
}
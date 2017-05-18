#include "Polygon.h"
#include <iostream>
#include <vector>

int main() {
    // Здесь должно быть чнение вешриш из файла
    // создание по ним класса Polygon
    // вызов метода и вывод триангуляции
    int n;
    std::cin >> n;
    std::vector<std::pair<double, double>> a(n);
    for (int i = 0; i < n; ++i) {
        double x, y;
        std::cin >> x >> y;
        a[i].first = x;
        a[i].second = y;
    }
    Polygon pol(a.begin(), a.end());
    auto t = pol.triangulation();
    for (const auto &i : t)
        std::cout << i.first.n << ' ' << i.second.n << std::endl;
    return 0;
}
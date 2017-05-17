#include <iostream>

int main() {
    // Здесь должно быть чнение вешриш из файла
    // создание по ним класса Polygon
    // вызов метода и вывод триангуляции
    int n;
    std::cin >> n;
    std::vector<std::pair<double>> a(n);
    for (int i = 0; i < n; ++i) {
        double x, y;
        std::cin >> x >> y;
        a[i].first = x;
        a[i].second = y;
    }
    Polygon pol(a.begin(), a.end());
    return 0;
}
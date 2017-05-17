#include "Polygon.h"
#include <exception>

template<typename Iter>

Polygon::Polygon(Iter begin, Iter end) {
    unsigned n = 0;
    while(begin != end) {
        vertexes.push_back(Vertex(begin->first, begin->second, n++));
        ++begin;
    }
}

bool Polygon::crossed (Vertex a, Vertex b, Vertex c, Vertex d) {
    return (intersect_1(a.x, b.x, c.x, d.x)
            && intersect_1(a.y, b.y, c.y, d.y)
            && (area(a, b, c) * area(a, b, d) <= 0)
            && (area(c, d, a) * area(c, d, b) <= 0));
}

bool Polygon::intersect_1 (double a, double b, double c, double d) {
    if (a > b) std::swap(a, b);
    if (c > d) std::swap(c, d);
    return max(a, c) <= min(b, d);
}

double Polygon::area (Vertex a, Vertex b, Vertex c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

std::list<std::pair<unsigned, unsigned>> Polygon::triangulation(std::vector<std::vector<double>>& subtasks,
                                                       std::list<Vertex>& vertexes) {
    double min = subtasks[0][0];
    std::vector<std::pair<Vertex, Vertex>> ans;
    for (size_t i = 0; i < subtasks.size(); ++i) {
        for (size_t j = 0; j < subtasks.size(); ++j) {
            if (subtasks[i][j] < min)
                min = subtasks[i][j];
        }
    }
    for (size_t i = 0; i < subtasks.size(); ++i) {
        for (size_t j = 0; j < subtasks.size(); ++j) {
            if (subtasks[i][j] != min)
                continue;
            Vertex a, b;
            a = std::find_if(vertexes.begin(), vertexes.end(), [&](const Vertex& v) { return v.n == i; } );
            a = std::find_if(vertexes.begin(), vertexes.end(), [&](const Vertex& v) { return v.n == j; } );
            bool flag = 1;
            for (size_t k = 0; k < ans.size(); ++k) {
                if (crossed(a, b, ans[k].first, ans[k].second)) {
                    flag = 0;
                    break;
                }
            }
            if (flag)
                ans.push_back(std::pair<Vertex, Vertex>(a, b));
        }
    }
};


#include "Polygon.h"
#include <algorithm>
#include <stdexcept>
#include <cmath>
#include <vector>

template<typename Iter>

Polygon::Polygon(Iter begin, Iter end) {
    unsigned n = 0;
    while(begin != end) {
        vertexes.push_back(Vertex(begin->first, begin->second, n++));
        ++begin;
    }
    if (n < 3)
        throw std::invalid_argument("Less then 3 vertexes in the polygon");
    Vertex first = vertexes.front();
    std::sort(vertexes.begin(), vertexes.end(), [&](const Vertex& v1, const Vertex& v2) {
        double v1x = v1.x - first.x;
        double v1y = v1.y - first.y;
        double v2x = v2.x - first.x;
        double v2y = v2.y - first.y;
        return v1x*v2y - v1y*v2x < 0;
    });
}

double Polygon::edgeLen(const Vertex& v1, const Vertex& v2) {
    double x = v2.x - v1.x;
    double y = v2.y - v1.y;
    return sqrt(x*x + y*y);
}


double Polygon::minTriangulationP(std::list<Vertex>& vertexes, std::vector<std::vector<double>>& subtasks) {
    if (vertexes.size() == 3) {
        auto v = vertexes.begin();
        double  triangleP  = edgeLen(*v,               *std::next(v, 1));
                triangleP += edgeLen(*v,               *std::next(v, 2));
                triangleP += edgeLen(*std::next(v, 1), *std::next(v, 2));
        return triangleP;
    }
    double minP = -1;
    for (auto i = vertexes.begin(); i != std::next(vertexes.end(), -2); ++i) {
        double triangleP;
        unsigned n = i->n;
        unsigned m = std::next(i, 2)->n;
        if (subtasks[n][m] >= 0 || subtasks [m][n] >= 0) {
            triangleP = subtasks[n][m] = subtasks[m][n];
        } else {
            triangleP  = edgeLen(*i,               *std::next(i, 1));
            triangleP += edgeLen(*std::next(i, 1), *std::next(i, 2));
            Vertex v = *i;
            auto next = vertexes.erase(i);
            triangleP += minTriangulationP(vertexes, subtasks);
            subtasks[n][m] = subtasks[m][n] = triangleP;
            vertexes.insert(next, v);
        }
        minP = std::min(minP, triangleP);
    }
    return minP;
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

std::list<std::pair<unsigned, unsigned>> Polygon::triangulation() const noexcept {
    std::vector<std::vector<double>> subtasks(vertexes.size(), std::vector<double>(std::vector<double>, -1));

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


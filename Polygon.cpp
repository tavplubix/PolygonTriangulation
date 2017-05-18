#include "Polygon.h"
#include <algorithm>
#include <cmath>
#include <vector>
#include <utility>

#include <iostream>

double Polygon::edgeLen(const Vertex& v1, const Vertex& v2) {
    double x = v2.x - v1.x;
    double y = v2.y - v1.y;
    return sqrt(x*x + y*y);
}


double Polygon::minTriangulationP(std::list<Vertex>& vertexes, std::vector<std::vector<double>>& subtasks, double P) const {
    std::vector<Vertex> debug(vertexes.begin(), vertexes.end());
    if (vertexes.size() == 3) {
        auto v = vertexes.begin();
        double  triangleP  = edgeLen(*v,               *std::next(v, 1));
                triangleP += edgeLen(*v,               *std::next(v, 2));
                triangleP += edgeLen(*std::next(v, 1), *std::next(v, 2));
        return P + triangleP;
    }
    double minP = std::numeric_limits<double>::infinity();
    for (auto i = vertexes.begin(); i != std::next(vertexes.end(), -2); ++i) {
        double triangleP;
        unsigned n = i->n;
        unsigned m = std::next(i, 2)->n;
        if (subtasks[n][m] >= 0 || subtasks [m][n] >= 0) {
            triangleP = subtasks[n][m] = subtasks[m][n];
        } else {
            triangleP  = edgeLen(*i,               *std::next(i, 1));
            triangleP += edgeLen(*std::next(i, 1), *std::next(i, 2));
            Vertex v = *std::next(i);
            auto next = vertexes.erase(std::next(i));
            triangleP = minTriangulationP(vertexes, subtasks, P + triangleP);
            subtasks[n][m] = subtasks[m][n] = triangleP;
            vertexes.insert(next, v);
        }
        minP = std::min(minP, triangleP);
    }
    return minP;
}

bool Polygon::crossed (Vertex a, Vertex b, Vertex c, Vertex d) const noexcept {
    if ((a == c && b == d) || (a == d && b == c))
        return true;
    if (a == c || a == d || b == c || b == d)
        return false;
    return (intersect_1(a.x, b.x, c.x, d.x)
            && intersect_1(a.y, b.y, c.y, d.y)
            && (area(a, b, c) * area(a, b, d) <= 0)
            && (area(c, d, a) * area(c, d, b) <= 0));
}

bool Polygon::intersect_1 (double a, double b, double c, double d) const noexcept{
    if (a > b) std::swap(a, b);
    if (c > d) std::swap(c, d);
    return std::max(a, c) <= std::min(b, d);
}

double Polygon::area (Vertex a, Vertex b, Vertex c) const noexcept {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

std::vector<std::pair<Vertex, Vertex>> Polygon::triangulation() const noexcept {
    std::vector<std::vector<double>> subtasks(vertexes.size(), std::vector<double>(vertexes.size(), -1));

    double min = minTriangulationP(vertexes, subtasks, 0);
    std::vector<std::pair<Vertex, Vertex>> ans;

    for (size_t i = 0; i < subtasks.size(); ++i) {
        for (size_t j = 0; j < subtasks.size(); ++j) {
            if (subtasks[i][j] != min)
                continue;
            Vertex a, b;
            a = *std::find_if(vertexes.begin(), vertexes.end(), [&](const Vertex& v) { return v.n == i; } );
            b = *std::find_if(vertexes.begin(), vertexes.end(), [&](const Vertex& v) { return v.n == j; } );
            bool flag = false;
            for (size_t k = 0; k < ans.size(); ++k)
                if (flag = crossed(a, b, ans[k].first, ans[k].second))
                    break;
            if (!flag)
                ans.push_back(std::pair<Vertex, Vertex>(a, b));
        }
    }
    return ans;
};


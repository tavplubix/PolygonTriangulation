#include "Polygon.h"
#include <stdexcept>
#include <cmath>

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



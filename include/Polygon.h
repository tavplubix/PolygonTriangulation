#pragma once
#include <algorithm>
#include <iostream>
#include <list>
#include <stdexcept>
#include <vector>

struct Vertex {
    double x, y;
    unsigned n;
    Vertex(double x = 0, double y = 0, unsigned n = 0) : x(x), y(y), n(n) {};
    bool operator == (const Vertex& other) const { return x == other.x && y == other.y; }
    bool operator != (const Vertex& other) const { return !(*this == other); }
};

typedef std::pair<Vertex, Vertex> Edge;

namespace simpleTests
{
    struct testPolygon;
    struct testPolygonMinTriangulationP;
}

#include <iostream>

class Polygon {
    friend struct ::simpleTests::testPolygon;
    friend struct ::simpleTests::testPolygonMinTriangulationP;
private:
    std::vector<Vertex> vertexes;
    double minTriangulationP(std::vector<std::vector<std::pair<double, size_t>>> &subtask, size_t i, size_t j) const noexcept;
public:
    Polygon() = delete;
    template<typename Iter>
    Polygon(Iter begin, Iter end) {
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
            return v1x*v2y - v1y*v2x > 0;
        });
    }
    template<typename Iteratable>
    Polygon(const Iteratable& vertexes) : Polygon(std::begin(vertexes), std::end(vertexes)) {}
    static double edgeLen(const Vertex& v1, const Vertex& v2);
    double triangulation(std::vector<Edge> &answer) const;
    double P() const noexcept;
};



#pragma once
#include <algorithm>
#include <list>
#include <stdexcept>
#include <vector>

struct Vertex {
    double x, y;
    unsigned n;
    Vertex(double x = 0, double y = 0, unsigned n = 0) : x(x), y(y), n(n) {};
    bool operator == (const Vertex& other) const { return x == other.x && y == other.y; }
};




class Polygon {
    mutable std::list<Vertex> vertexes;

    // Находит минимальный периметр триангуляции многоугольника с вершинами vertexes,
    // записывая в subtasks результаты решения подзадач
    double minTriangulationP(std::list<Vertex>& vertexes, std::vector<std::vector<double>>& subtasks, double P) const;
    double area (Vertex a, Vertex b, Vertex c) const noexcept;
    bool intersect_1 (double a, double b, double c, double d) const noexcept;
    bool crossed (Vertex a, Vertex b, Vertex c, Vertex d) const noexcept;
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
        vertexes.sort([&](const Vertex& v1, const Vertex& v2) {
            double v1x = v1.x - first.x;
            double v1y = v1.y - first.y;
            double v2x = v2.x - first.x;
            double v2y = v2.y - first.y;
            return v1x*v2y - v1y*v2x > 0;
        });
    }
    static double edgeLen(const Vertex& v1, const Vertex& v2);
    std::vector<std::pair<Vertex, Vertex>> triangulation() const noexcept;
};



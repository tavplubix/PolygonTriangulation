#pragma once
#include <algorithm>
#include <list>

struct Vertex {
    double x, y;
    unsigned n;
    Vertex(x, y, n) : x(x), y(y), n(n) {};
};




class Polygon {
    mutable std::list<Vertex> vertexes;

    // Находит минимальный периметр триангуляции многоугольника с вершинами vertexes,
    // записывая в subtasks результаты решения подзадач
    double minTriangulationP(std::list<Vertex>& vertexes, std::vector<std::vector<double>>& subtasks);
    double area (Vertex a, Vertex b, Vertex c);
    bool intersect_1 (double a, double b, double c, double d);
    bool crossed (Vertex a, Vertex b, Vertex c, Vertex d);
public:
    Polygon() = delete;
    template<typename Iter>
    Polygon(Iter begin, Iter end);
    static edgeLen(const Vertex& v1, const Vertex& v2) noexcept;
    std::list<std::pair<unsigned, unsigned>> triangulation() const noexcept;
};



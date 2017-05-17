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
public:
    Polygon() = delete;
    template<typename Iter>
    Polygon(Iter begin, Iter end);
    static edgeLen(const Vertex& v1, const Vertex& v2) noexcept;
    std::list<unsigned> triangulation() const noexcept;
};



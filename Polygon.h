#pragma once
#include <algorithm>
#include <list>
#include <vector>

struct Vertex {
    double x, y;
    unsigned n;
    Vertex(double x, double y, unsigned n) : x(x), y(y), n(n) {};
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
    static double edgeLen(const Vertex& v1, const Vertex& v2);
    std::list<unsigned> triangulation() const noexcept;
};



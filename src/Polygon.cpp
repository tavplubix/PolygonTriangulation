#include "Polygon.h"
#include <algorithm>
#include <cmath>
#include <functional>
#include <vector>
#include <utility>


double Polygon::edgeLen(const Vertex& v1, const Vertex& v2) {
    double x = v2.x - v1.x;
    double y = v2.y - v1.y;
    return sqrt(x*x + y*y);
}


double Polygon::minTriangulationP(std::vector<std::vector<std::pair<double, size_t>>> &subtasks, size_t i, size_t j) const noexcept {
    if (subtasks[i][j].first >= 0)
        return subtasks[i][j].first;
    if (j - i == 1)
        return subtasks[i][j].first = edgeLen(vertexes[i], vertexes[j]);
    if (j - i == 2) {
        double  triangleP  = edgeLen(vertexes[i  ], vertexes[i+1]);
                triangleP += edgeLen(vertexes[i  ], vertexes[i+2]);
                triangleP += edgeLen(vertexes[i+1], vertexes[i+2]);
        return subtasks[i][j].first = triangleP;
    }
    double minP = std::numeric_limits<double>::infinity();
    size_t minPk = 0;
    for (size_t k = i+1; k < j; ++k) {
        double P = edgeLen(vertexes[i], vertexes[j]);
        P += minTriangulationP(subtasks, i, k);
        P += minTriangulationP(subtasks, k, j);
        if (P < minP) {
            minP = P;
            minPk = k;
        }
    }
    subtasks[i][j].second = minPk;
    return subtasks[i][j].first = minP;
}

double Polygon::triangulation(std::vector<Edge> &answer) const {
    std::vector<std::vector<std::pair<double, size_t>>>
            subtasks(vertexes.size(), std::vector<std::pair<double, size_t>>(vertexes.size(),
                                                                             std::pair<double, size_t>(-1, 0)));
    double minP = minTriangulationP(subtasks, 0, vertexes.size() - 1);

    std::function<void(size_t,size_t)> restoreAnswer = [&](size_t i, size_t j) {
        size_t minPk = subtasks[i][j].second;
        if (j - i < 3)
            return;
        if (minPk - i > 1)
            answer.push_back(std::make_pair(vertexes[i], vertexes[minPk]));
        if (j - minPk > 1)
            answer.push_back(std::make_pair(vertexes[minPk], vertexes[j]));
        restoreAnswer(i, minPk);
        restoreAnswer(minPk, j);
    };

    restoreAnswer(0, vertexes.size() - 1);
    return minP;
};

double Polygon::P() const noexcept {
    double P = edgeLen(*vertexes.begin(), *std::next(vertexes.end(), -1));
    for (auto i = vertexes.begin(); i != std::next(vertexes.end(), -1); ++i)
        P += edgeLen(*i, *std::next(i));
    return P;
}


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



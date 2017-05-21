#include "Polygon.h"

#include <cmath>
#include <vector>
#include <initializer_list>


#define p(x, y) std::pair<double, double>(x, y)
#define v(x, y, n) Vertex(x, y, n)
typedef std::vector<std::pair<double, double>> VL;

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#define BOOST_TEST_MODULE testPolygon

#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>


BOOST_AUTO_TEST_SUITE(simpleTests)

    BOOST_AUTO_TEST_CASE(testPolygon) {
        //Проверяет, что конструктор Polygon бросает исключение, если вершин меньше трёх
        BOOST_CHECK_THROW(Polygon pol((VL())                ), std::invalid_argument);
        BOOST_CHECK_THROW(Polygon pol(VL({p(0, 0)         })), std::invalid_argument);
        BOOST_CHECK_THROW(Polygon pol(VL({p(0, 0), p(1, 1)})), std::invalid_argument);

        //Проверяет, что конструктор Polygon правильно сортирует вершины
        VL v = {p(0, 0), p(1, 1), p(1, 0), p(0, 1)};
        std::vector<Vertex> sorted = {v(0, 0, 0), v(1, 0, 1), v(1, 1, 2), v(0, 1, 3)};
        BOOST_REQUIRE_NO_THROW(Polygon pol(v));
        Polygon pol(v);
        BOOST_CHECK(pol.vertexes == sorted);
        // TODO: нужно больше тестов
    }

    BOOST_AUTO_TEST_CASE(testPolygonEdgeLen) {      // Проверяет, правильно ли вычисляется длина рёбер
        BOOST_CHECK_EQUAL(Polygon::edgeLen(Vertex(2, 0), Vertex(42,  0)), 40);
        BOOST_CHECK_EQUAL(Polygon::edgeLen(Vertex(0, 2), Vertex( 0, 42)), 40);
        BOOST_CHECK_EQUAL(Polygon::edgeLen(Vertex(1, 2), Vertex( 2,  3)), sqrt(2));
        // TODO: нужно больше тестов
    }

    BOOST_AUTO_TEST_CASE(testPolygonP) {        // Проверяет, правильно ли вычисляется периметр
        BOOST_CHECK_EQUAL(Polygon(VL({p(0, 0), p(1, 1), p(1, 0), p(0, 1)})).P(), 4);
        BOOST_CHECK_EQUAL(Polygon(VL({p(0, 0), p(2, 2), p(2, 0), p(0, 2)})).P(), 8);
        BOOST_CHECK_EQUAL(Polygon(VL({p(0, 0), p(1, 1), p(1, 0)         })).P(), 2 + sqrt(2));
        // TODO: нужно больше тестов
    }

// Этот макрос создаёт массив для хранения результатов решения подзадач,
// который можно передать в Polygon::minTriangulationP
#define subtasksArr(size)  std::vector<std::vector<std::pair<double, size_t>>> \
                                (size, std::vector<std::pair<double, size_t>> \
                                            (size, std::pair<double, size_t>(-1, 0)))
// Вызывает Polygon::minTriangulationP
#define minTP(v, subtasks) (Polygon(v).minTriangulationP(subtasks, 0, v.size()-1) - Polygon(v).P())

    // Проверяет, правильно ли находится минимальный суммарный периметр триангуляции
    BOOST_AUTO_TEST_CASE(testPolygonMinTriangulationP) {
        auto subtasks = subtasksArr(3);
        BOOST_CHECK_EQUAL(minTP(VL({p(-1337, 228), p(42, 3.14), p(0.007, -265)}), subtasks), 0);
        subtasks = subtasksArr(4);
        BOOST_CHECK_CLOSE(minTP(VL({p(0, 0), p(1, 1), p(1, 0), p(0, 1)}), subtasks), sqrt(2), 0.0001);

        // TODO: НУЖНО БОЛЬШЕ ТЕСТОВ
    }

    // TODO: добавить тесты для Polygon::triangulation (учесть, что может быть несколько правильных ответов)

    // TODO: добавить тесты на большом наборе вершин, проверяющие O(n^3)

BOOST_AUTO_TEST_SUITE_END()
cmake_minimum_required(VERSION 3.7)
project(PolygonTriangulation)

include_directories(include/)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -O0 -fno-elide-constructors" )

set(SOURCE_FILES src/main.cpp src/Polygon.cpp)
add_executable(PolygonTriangulation ${SOURCE_FILES})


set(TESTS_SOURCES
        ./test/polygon_simple_tests.cpp src/Polygon.cpp)
find_package (Boost COMPONENTS unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
set(TEST test_Polygon)
add_executable(${TEST} ${TESTS_SOURCES})
target_link_libraries(${TEST} ${PROJECT} ${Boost_LIBRARIES})
enable_testing()
add_test(${TEST} ${TEST})
ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

enable_testing()
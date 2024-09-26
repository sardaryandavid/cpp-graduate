cmake_minimum_required(VERSION 3.10)

project(tests VERSION 1.0)

find_package(GTest)

add_compile_options(
    -Werror
    -Wall
    -Wextra
    -Wpedantic
)

set(SOURCES tests.cpp
            ../src/point.cpp
            ../src/vector.cpp
            ../src/plane.cpp
            ../src/triangle.cpp
            ../src/line_segm.cpp)

add_executable(test ${SOURCES})
target_link_libraries(test GTest::gtest GTest::gmock pthread)
target_include_directories(test PRIVATE ../include)
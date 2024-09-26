cmake_minimum_required(VERSION 3.10)

project(triangles VERSION 1.0)

add_compile_options(
    -Werror
    -Wall
    -Wextra
    -Wpedantic
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(SOURCES src/main.cpp
            src/point.cpp
            src/vector.cpp
            src/plane.cpp
            src/triangle.cpp
            src/line_segm.cpp)

add_executable(triangles ${SOURCES})
target_include_directories(triangles PRIVATE include)

if (DEBUG)
  add_definitions(-DDEBUG)
endif()

if (BENCH)
  add_subdirectory(bench)
endif()

if (TEST)
  add_subdirectory(tests)
endif()
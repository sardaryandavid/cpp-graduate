cmake_minimum_required(VERSION 3.10)

project(bench VERSION 1.0)

add_compile_options(
    -Werror
    -Wall
    -Wextra
    -Wpedantic
)

add_executable(bench bench.cpp)
target_include_directories(bench PRIVATE ../include)
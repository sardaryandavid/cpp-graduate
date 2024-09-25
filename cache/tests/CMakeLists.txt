cmake_minimum_required(VERSION 3.10)

project(tests VERSION 1.0)

find_package(GTest REQUIRED)

add_compile_options(
    -Werror
    -Wall
    -Wextra
    -Wpedantic
)

add_executable(test tests.cpp)
target_link_libraries(test GTest::gtest GTest::gmock pthread)
target_include_directories(test PRIVATE ../include)
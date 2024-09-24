cmake_minimum_required(VERSION 3.10)

project(caches VERSION 1.0)

add_compile_options(
    -Werror
    -Wall
    -Wextra
    -Wpedantic
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable(lfu src/cache.cpp)
add_executable(belady src/belady.cpp)
target_include_directories(lfu PRIVATE include)
target_include_directories(belady PRIVATE include)

if (DEBUG)
  add_definitions(-DDEBUG)
endif()

if (BDEBUG)
  add_definitions(-DBDEBUG)
endif()

if (BENCH)
  add_subdirectory(bench)
endif()

if (TEST)
  add_subdirectory(tests)
endif()
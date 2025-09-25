cmake_minimum_required(VERSION 3.5)
project(rpn_calc_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(SOURCES src/main.cpp src/expr_tree.cpp)
add_executable(calc ${SOURCES})

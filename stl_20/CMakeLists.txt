cmake_minimum_required(VERSION 3.21)
project(stl_20)

set(CMAKE_CXX_STANDARD 20)

add_executable(stl_20 main.cpp simple_string.cpp simple_string.h bubble_sort.cpp bubble_sort.h generate_data.h insertion_sort.cpp insertion_sort.h time_sort.h heap_sort.h)

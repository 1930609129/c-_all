cmake_minimum_required(VERSION 3.21)
project(stl)

set(CMAKE_CXX_STANDARD 14)

add_executable(stl main.cpp semaphore.cpp semaphore.h min.h pair.cpp pair.h simple_string.cpp simple_string.h container.cpp container.h memblock.cpp memblock.h point.cpp point.h)

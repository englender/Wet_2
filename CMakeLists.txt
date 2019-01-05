cmake_minimum_required(VERSION 3.9)
project(new_WET2)

set(CMAKE_CXX_STANDARD 11)

add_executable(new_WET2 main.cpp
        map_tree.h
        node_list.h
        UnionFindPixel.cpp
        UnionFindPixel.h
        Image.h
        Image.cpp)
cmake_minimum_required(VERSION 3.30)
project(task1_3)

set(CMAKE_CXX_STANDARD 20)

add_library(task1 STATIC
        task1/stringlist.cpp
        task1/stringlist.h)

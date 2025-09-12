cmake_minimum_required(VERSION 3.30)
project(task1_3)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)
enable_testing()

add_library(task1 STATIC
        task1/stringlist.cpp
        task1/stringlist.h)

add_executable(task1_test task1/test.cpp)
target_link_libraries(task1_test PRIVATE task1 GTest::gtest_main)
gtest_discover_tests(task1_test)

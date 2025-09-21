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

add_executable(task2
        task2/anytype.h
        task2/main.cpp)

add_executable(task2_test task2/test.cpp)
target_link_libraries(task2_test PRIVATE GTest::gtest_main)
gtest_discover_tests(task2_test)

add_library(task3_lib STATIC
        task3/FileFinder.cpp
        task3/FileFinder.h
        task3/FileStats.cpp
        task3/FileStats.h)

add_executable(task3 task3/task3.cpp)
target_link_libraries(task3 PRIVATE task3_lib)

add_executable(task3_test
        task3/test_stats.cpp
        task3/gets_string.cpp
        task3/gets_string.h)
target_link_libraries(task3_test PRIVATE task3_lib GTest::gtest_main)
gtest_discover_tests(task3_test)

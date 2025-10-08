cmake_minimum_required(VERSION 3.19)
project(tiny_sql)

set(CMAKE_CXX_STANDARD 14)

add_executable(tiny_sql Implementation/main.cpp Implementation/Column.cpp)
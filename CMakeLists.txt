cmake_minimum_required(VERSION 3.19)
project(tiny_sql)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES "src/*.cpp")

add_executable(tiny_sql  ${SOURCES})


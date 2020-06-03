cmake_minimum_required(VERSION 3.13.1)

SET(CMAKE_C_COMPILER "/usr/local/bin/gcc")
SET(CMAKE_CXX_COMPILER "/usr/local/bin/g++")

project(Session3)
set(CMAKE_CXX_STANDARD 17)
add_definitions(-std=c++17)
add_executable(Session3 main.cpp)

target_link_libraries(Session3
    pthread
)

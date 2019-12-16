cmake_minimum_required(VERSION 3.13.1) 
project(Session4)
set(CMAKE_CXX_STANDARD 17)
add_definitions(-std=c++17)
add_executable(Session4 main.cpp)
target_link_libraries(Session4
    pthread
)

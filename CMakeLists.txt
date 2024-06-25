cmake_minimum_required(VERSION 3.10)
project(CFLReachability)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

add_executable(run
    src/main.cpp
    src/graph.cpp
    src/reachability.cpp
)
cmake_minimum_required(VERSION 3.17)
project(SwampyGraph)

set(CMAKE_CXX_STANDARD 17)

add_executable(SwampyGraph main.cpp Vertex.cpp Vertex.h Edge.cpp Edge.h Color.h Graph.cpp Graph.h)
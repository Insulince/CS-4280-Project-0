cmake_minimum_required(VERSION 3.8)
project(P0)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp EBSTNode.cpp EBSTNode.h EBST.cpp EBST.h traversals.h)
add_executable(P0 ${SOURCE_FILES})
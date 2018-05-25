cmake_minimum_required(VERSION 2.8)

project(compression)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Werror")

add_executable(${PROJECT_NAME} "main.cpp" "ICompression.h" "huffman.h" "huffman.cpp")

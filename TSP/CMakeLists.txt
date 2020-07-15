cmake_minimum_required(VERSION 3.16)
project(TSP)

set(CMAKE_CXX_STANDARD 14)

add_executable(TSP main.cpp header.h readFile/readFile.cpp readFile/readFile.h)
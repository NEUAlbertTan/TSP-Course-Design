cmake_minimum_required(VERSION 3.16)
project(TSP)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(readFile)
include_directories(readFile)
add_subdirectory(testAlgo)
include_directories(testAlgo)
add_subdirectory(Ant)
include_directories(Ant)


add_executable(TSP main.cpp )

target_link_libraries(TSP testAlgo)
target_link_libraries(TSP readFile)
target_link_libraries(TSP ant)
cmake_minimum_required(VERSION 3.16)
project(TSP)

set(CMAKE_CXX_STANDARD 14)

# 编译模式
#SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_BUILD_TYPE "Release")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O1 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

add_subdirectory(readFile)
include_directories(readFile)
add_subdirectory(testAlgo)
include_directories(testAlgo)
add_subdirectory(Ant)
include_directories(Ant)
add_subdirectory(Tabu)
include_directories(Tabu)
add_subdirectory(insertion)
include_directories(insertion)
add_subdirectory(greedyKNN)
include_directories(greedyKNN)

add_executable(TSP main.cpp)

target_link_libraries(TSP testAlgo)
target_link_libraries(TSP readFile)
target_link_libraries(TSP ant)
target_link_libraries(TSP tabu)
target_link_libraries(TSP insertion)
target_link_libraries(TSP greedyKNN)
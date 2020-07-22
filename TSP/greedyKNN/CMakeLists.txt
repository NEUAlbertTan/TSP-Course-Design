project(greedyKNN)

set(HEADER_FILES
        greedyKNN.h
        )

set(SOURCE_FILES
        greedyKNN.cpp
        greedyKNN.cpp)

add_library(greedyKNN STATIC ${SOURCE_FILES} ${HEADER_FILES})
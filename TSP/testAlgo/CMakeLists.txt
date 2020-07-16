project(testAlgo)

set(HEADER_FILES
        testAlgo.h
        )

set(SOURCE_FILES
        testAlgo.cpp
        )

add_library(testAlgo STATIC ${SOURCE_FILES} ${HEADER_FILES})
project(tabu)

set(HEADER_FILES
        tabu.h
        )

set(SOURCE_FILES
        tabu.cpp
        )

add_library(tabu STATIC ${SOURCE_FILES} ${HEADER_FILES})
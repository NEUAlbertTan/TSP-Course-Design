project(ant)

set(HEADER_FILES
        ant.h
        )

set(SOURCE_FILES
        ant.cpp
        )

add_library(ant STATIC ${SOURCE_FILES} ${HEADER_FILES})
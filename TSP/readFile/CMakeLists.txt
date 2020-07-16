project(readFile)

set(HEADER_FILES
        readFile.h
        )

set(SOURCE_FILES
        readFile.cpp
        )

add_library(readFile STATIC ${SOURCE_FILES} ${HEADER_FILES})
project(insertion)

set(HEADER_FILES
        insertion.h
        )

set(SOURCE_FILES
        insertion.cpp
        )

add_library(insertion STATIC ${SOURCE_FILES} ${HEADER_FILES})
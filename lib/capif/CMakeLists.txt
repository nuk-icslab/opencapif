cmake_minimum_required (VERSION 3.2)

set(LIB_NAME capif)

file(GLOB_RECURSE SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(${LIB_NAME} SHARED ${SRCS})
target_include_directories(${LIB_NAME} PUBLIC
    include/
)
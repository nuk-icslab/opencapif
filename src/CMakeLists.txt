cmake_minimum_required (VERSION 3.2)

set(CCF_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ccf)

file(GLOB CCF_SRCS
    ${CCF_DIR}/api_impl/*.cpp
    ${CCF_DIR}/*.cpp
)
file(GLOB CCF_HEADERS
    ../include/ccf/*.h
)

add_library(CCF STATIC ${CCF_SRCS} ${CCF_HEADERS})
target_include_directories(CCF PUBLIC
    ../include/
    ../include/ccf/
    ../include/openapi/api/
    ../include/openapi/model/
)
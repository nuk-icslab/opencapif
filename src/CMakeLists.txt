cmake_minimum_required (VERSION 3.2)

#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED True)

#include_directories(../include/capif_core_function)
#include_directories(../lib/include)

set(CCF_DIR ${CMAKE_CURRENT_SOURCE_DIR}/capif_core_function)

file(GLOB CCF_SRCS
    ${CCF_DIR}/api_impl/*.cpp
    ${CCF_DIR}/*.cpp
)
file(GLOB CCF_HEADERS
    ../include/capif_core_funcation/*.h
)

add_library(CCF STATIC ${CCF_SRCS} ${CCF_HEADERS})
target_include_directories(CCF PUBLIC
    ../include/
    ../include/capif_core_function/
    ../include/openapi/api/
    ../include/openapi/model/
)
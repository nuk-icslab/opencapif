cmake_minimum_required (VERSION 3.2)

project(capif_core_function LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pg -g3" )

set(CCF_NAME capif_core_function)

add_subdirectory(lib)
add_subdirectory(src)

add_executable(${CCF_NAME} src/capif_core_function/ccf_main.cpp)
target_link_libraries(${CCF_NAME} PUBLIC OpenAPI CCF pistache pthread)
target_include_directories(${CCF_NAME} PUBLIC
                          include/
                          )
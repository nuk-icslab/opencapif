cmake_minimum_required (VERSION 3.2)

project(capif LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CCF_NAME ccf)

add_subdirectory(lib)
add_subdirectory(src)

add_executable(${CCF_NAME} src/ccf/ccf_main.cpp)
target_link_libraries(${CCF_NAME} PUBLIC OpenAPI CCF pistache pthread)
target_include_directories(${CCF_NAME} PUBLIC
                          include/
                          )
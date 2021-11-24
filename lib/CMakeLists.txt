cmake_minimum_required (VERSION 3.2)

file(GLOB OPENAPI_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/openapi/api/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/openapi/model/*.cpp
)

file(GLOB OPENAPI_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/openapi/api/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/openapi/model/*.h
)

add_library(OpenAPI SHARED ${OPENAPI_SRCS} ${OPENAPI_HEADERS})
target_include_directories(OpenAPI PUBLIC
    ../include/openapi/api/
    ../include/openapi/model/
)
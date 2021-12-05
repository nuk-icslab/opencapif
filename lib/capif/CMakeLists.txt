cmake_minimum_required (VERSION 3.2)
include(FindPkgConfig)

set(LIB_NAME capif)
message("lib${LIB_NAME} version: ${CMAKE_PROJECT_VERSION}")

file(GLOB_RECURSE SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

find_package(nlohmann_json REQUIRED)
pkg_check_modules(LIBPISTACHE libpistache)

add_library(${LIB_NAME} SHARED ${SRCS})
target_link_libraries(${LIB_NAME} PUBLIC
                     nlohmann_json::nlohmann_json
                     ${LIBPISTACHE_LIBRARIES}
                     )
target_include_directories(${LIB_NAME} PUBLIC
    include/
    ${LIBPISTACHE_INCLUDE_DIRS}
)
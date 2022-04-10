cmake_minimum_required (VERSION 3.2)
include(FindPkgConfig)

project(ccf LANGUAGES CXX VERSION 0.1.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(OPENAPI_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../lib/openapi/ccf/pistache)

#set(CMAKE_VERBOSE_MAKEFILE ON)

# Get the latest commit hash
execute_process(
    COMMAND git rev-parse HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE)
write_file(.VERSION "${CMAKE_PROJECT_VERSION}")
message("${CMAKE_PROJECT_NAME} version: ${CMAKE_PROJECT_VERSION} (${GIT_COMMIT_HASH})")

# Check dependencies
find_package(PkgConfig)
find_package(Threads REQUIRED)
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)
pkg_check_modules(LIBMONGOCXX libmongocxx)
pkg_check_modules(LIBBSONCXX libbsoncxx)
pkg_check_modules(Pistache REQUIRED IMPORTED_TARGET libpistache)

include_directories(${OPENAPI_SRC_DIR}/model)
include_directories(${OPENAPI_SRC_DIR}/api)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/impl)
include_directories(${LIBMONGOCXX_INCLUDE_DIRS})
include_directories(${LIBBSONCXX_INCLUDE_DIRS})

file(GLOB_RECURSE CCF_SRCS
    ${OPENAPI_SRC_DIR}/model/*.cpp
    ${OPENAPI_SRC_DIR}/api/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(${PROJECT_NAME} ${CCF_SRCS})
add_compile_definitions(__CCF_VERSION__="${CMAKE_PROJECT_VERSION}")
target_link_libraries(${PROJECT_NAME} PUBLIC
                     Threads::Threads
                     spdlog::spdlog
                     fmt::fmt
                     yaml-cpp
                     PkgConfig::Pistache
                     nlohmann_json::nlohmann_json
                     ${LIBMONGOCXX_LIBRARIES}
                     ${LIBBSONCXX_LIBRARIES}
                     )
configure_file(ccf.yaml config/ccf.yaml)
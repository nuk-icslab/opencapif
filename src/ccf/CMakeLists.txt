cmake_minimum_required (VERSION 3.2)
include(FindPkgConfig)
include(ExternalProject)

project(ccf LANGUAGES CXX VERSION 0.1.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(EXTERNAL_INSTALL_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/external)
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

ExternalProject_Add(PISTACHE
    GIT_REPOSITORY https://github.com/pistacheio/pistache.git
    BUILD_IN_SOURCE true
    INSTALL_COMMAND meson setup build --prefix=${EXTERNAL_INSTALL_LOCATION} --libdir=lib && meson install -C build
)

ExternalProject_Add(NLOHMANN
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION} -DJSON_BuildTests=OFF
)

include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

file(GLOB_RECURSE CCF_SRCS
    ${OPENAPI_SRC_DIR}/model/*.cpp
    ${OPENAPI_SRC_DIR}/api/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/impl/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

# Check dependencies
find_package(Threads REQUIRED)
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)
find_package(yaml-cpp REQUIRED)
pkg_check_modules(LIBMONGOCXX libmongocxx)
pkg_check_modules(LIBBSONCXX libbsoncxx)

add_executable(${PROJECT_NAME} ${CCF_SRCS})
add_dependencies(${PROJECT_NAME} PISTACHE NLOHMANN)
add_compile_definitions(__CCF_VERSION__="${CMAKE_PROJECT_VERSION}")
target_link_libraries(${PROJECT_NAME} PUBLIC
                     pistache
                     Threads::Threads
                     spdlog::spdlog
                     fmt::fmt
                     yaml-cpp
                     ${LIBMONGOCXX_LIBRARIES}
                     ${LIBBSONCXX_LIBRARIES}
                     )
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/impl)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${OPENAPI_SRC_DIR}/model)
include_directories(${OPENAPI_SRC_DIR}/api)
include_directories(${LIBMONGOCXX_INCLUDE_DIRS})
include_directories(${LIBBSONCXX_INCLUDE_DIRS})
configure_file(ccf.yaml config/ccf.yaml)
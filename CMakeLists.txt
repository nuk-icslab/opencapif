cmake_minimum_required (VERSION 3.2)
include(FindPkgConfig)

project(capif LANGUAGES CXX VERSION 0.1.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#set(CMAKE_VERBOSE_MAKEFILE ON)

# Get the latest commit hash
execute_process(
    COMMAND git rev-parse HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE)
write_file(.VERSION "${CMAKE_PROJECT_VERSION}")
message("${CMAKE_PROJECT_NAME} version: ${CMAKE_PROJECT_VERSION} (${GIT_COMMIT_HASH})")

add_subdirectory(lib/capif)
add_subdirectory(example)

#add_compile_definitions(DEBUG_CURL)

set(CCF_NAME ccf)

file(GLOB_RECURSE CCF_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ccf/*.cpp
)

# Check dependencies
find_package(Threads REQUIRED)
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)
pkg_check_modules(LIBMONGOCXX libmongocxx)
pkg_check_modules(LIBBSONCXX libbsoncxx)

add_executable(${CCF_NAME} ${CCF_SRCS})
add_compile_definitions(__CCF_VERSION__="${CMAKE_PROJECT_VERSION}")
target_link_libraries(${CCF_NAME} PUBLIC
                     capif
                     Threads::Threads
                     spdlog::spdlog
                     fmt::fmt
                     ${LIBMONGOCXX_LIBRARIES}
                     ${LIBBSONCXX_LIBRARIES}
                     )
target_include_directories(${CCF_NAME} PUBLIC
                          lib/capif/include/
                          ${LIBMONGOCXX_INCLUDE_DIRS}
                          ${LIBBSONCXX_INCLUDE_DIRS}
                          )
#========
set(APF_NAME apf)

file(GLOB_RECURSE APF_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/common/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/apf/*.cpp
)

# Check dependencies
find_package(CURL REQUIRED)
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)

add_library(${APF_NAME} SHARED ${APF_SRCS})
target_link_libraries(${APF_NAME} PUBLIC
                     capif
                     spdlog::spdlog
                     fmt::fmt
                     ${CURL_LIBRARIES}
                     )
target_include_directories(${APF_NAME} PUBLIC
                          lib/capif/include/
                          include/
                          ${CURL_INCLUDE_DIRS}
                          )

#========
set(INVOKER_NAME capifinvoker)

file(GLOB_RECURSE INVOKER_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/common/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/invoker/*.cpp
)

# Check dependencies
find_package(CURL REQUIRED)
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)

add_library(${INVOKER_NAME} SHARED ${INVOKER_SRCS})
target_link_libraries(${INVOKER_NAME} PUBLIC
                     capif
                     spdlog::spdlog
                     fmt::fmt
                     ${CURL_LIBRARIES}
                     )
target_include_directories(${INVOKER_NAME} PUBLIC
                          lib/capif/include/
                          include/
                          ${CURL_INCLUDE_DIRS}
                          )
